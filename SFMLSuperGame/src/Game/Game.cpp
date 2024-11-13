#include "Game.h"
#include "./../Core/ResourceManager.h"
#include "../GameEntities/Orc.h"


Game::Game()
{
    
}

void Game::initializeTileTexturesLevelOne() {

    for (int i = 0; i < NUM_LEVEL_TEXTURES; i++) {
        if (!tileTexturesLevelOne[i].loadFromFile(texturesPathlevelOne[i])) {
            std::cerr << "Failed to load texture: " << texturesPathlevelOne[i].toAnsiString() << std::endl;
        } else {
            std::cout << "Successfully loaded texture: " << texturesPathlevelOne[i].toAnsiString() << std::endl;
        }
    }
}

GameMap* Game::loadGameMap(const std::string& basePath)
{
    std::string mapPath = basePath + "/gameMap.dat";
    std::ifstream mapFile(mapPath);

    if (mapFile.is_open()) {
        std::string key;
        int cellSize = 0, screenWidth = 0, screenHeight = 0, mapSize = 0, mapSections = 0;
        
        // Read basic properties using key-value pairs
        while (mapFile >> key) {
            if (key == "cellSize") {
                mapFile >> cellSize;
            }
            else if (key == "screenWidth") {
                mapFile >> screenWidth;
            }
            else if (key == "screenHeight") {
                mapFile >> screenHeight;
            }
            else if (key == "mapSize") {
                mapFile >> mapSize;
            }
            else if (key == "mapSections") {
                mapFile >> mapSections;
            }
        }
        
        mapFile.close();
        
        // Create new GameMap with loaded properties
        gameMap = new GameMap(cellSize, screenWidth, screenHeight, mapSize);
        if (gameMap) {
            gameMap->mapSections = mapSections;
            
            gameMap->createSections(mapSections);
            
            // Load textures
            sf::Texture tileTextures[NUM_LEVEL_TEXTURES];
            for (int i = 0; i < NUM_LEVEL_TEXTURES; i++) {
                if (texturesPathlevelOne[i] != "none") {
                    if (!tileTextures[i].loadFromFile(texturesPathlevelOne[i])) {
                        std::cerr << "Failed to load texture: " << texturesPathlevelOne[i].toAnsiString() << std::endl;
                    }
                }
            }
            
            // Load each map section
            for (int i = 0; i < mapSections; i++) {
                loadMapSection(gameMap, basePath, i, tileTextures);
            }
            
            std::cout << "Game map loaded successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to open game map file: " << mapPath << std::endl;
    }

    return gameMap;
}

bool Game::loadMapSection(GameMap* gameMap, const std::string& basePath, int sectionIndex, sf::Texture* textures) {
    std::string sectionPath = basePath + "/mapSection_" + std::to_string(sectionIndex) + ".dat";
    std::ifstream sectionFile(sectionPath);
    
    if (!sectionFile.is_open()) {
        std::cerr << "Failed to load section file: " << sectionPath << std::endl;
        return false;
    }

    int cellSize = gameMap->cellSize;
    
    std::string line, key;
    int mapSectionPositionX = 0, numberOfCellsPerRow = 0;

    // Read section header
    while (std::getline(sectionFile, line)) {
        std::istringstream iss(line);
        iss >> key;

        if (key == "mapSectionPositionX") {
            iss >> mapSectionPositionX;
        }
        else if (key == "numberOfCellsPerRow") {
            iss >> numberOfCellsPerRow;
            break;
        }
    }

    // Create section if not exists
    if (!gameMap->sections[sectionIndex]) {
        gameMap->sections[sectionIndex] = new MapSection(mapSectionPositionX, numberOfCellsPerRow);
    }

    // Read tile data
    while (std::getline(sectionFile, line)) {
        if (line.find("TileCell[") == 0) {
            int row, col;
            sscanf_s(line.c_str(), "TileCell[%d][%d]", &row, &col);
            
            std::istringstream iss(line);
            std::string temp;
            iss >> temp; // Skip the TileCell[x][y] part
            
            TileCell& cell = gameMap->sections[sectionIndex]->tilecellArray[row][col];
            float xPos = 0.0f;
            float yPos = 0.0f;
            
            while (iss >> key) {
                if (key == "cellSize") {
                    iss >> cell.cellSize;
                    if(cell.cellSize == 8)
                    {
                        cell.cellSize = 32;
                    }
                }
                else if (key == "cellType") {
                    iss >> cell.cellType;
                }
                else if (key == "textureID") {
                    int textureID;
                    iss >> textureID;
                    
                    // Set texture ID but don't store texture
                    cell.textureID = textureID;
                    
                    // Only set up sprite if valid texture ID
                    if (textureID >= 0 && textureID < NUM_LEVEL_TEXTURES) {
                        cell.sprite.setTexture(tileTexturesLevelOne[textureID], true);
                        sf::Vector2u textureSize = tileTexturesLevelOne[textureID].getSize();
                        float scaleX = static_cast<float>(cell.cellSize) / textureSize.x;
                        float scaleY = static_cast<float>(cell.cellSize) / textureSize.y;
                        cell.sprite.setScale(scaleX, scaleY);
                    }
                }
                else if (key == "textureID") {
                    int textureID;
                    iss >> textureID;
                    cell.textureID = textureID;
                    // Set texture if valid
                    if (textureID >= 0 && textureID < NUM_LEVEL_TEXTURES) {
                        cell.sprite.setTexture(tileTexturesLevelOne[textureID], true);
                        sf::Vector2u textureSize = tileTexturesLevelOne[textureID].getSize();
                        float scaleX = static_cast<float>(cell.cellSize) / textureSize.x;
                        float scaleY = static_cast<float>(cell.cellSize) / textureSize.y;
                        cell.sprite.setScale(scaleX, scaleY);
                    }
                }
                else if (key == "xPos") {
                    iss >> xPos;
                }
                else if (key == "yPos") {
                    iss >> yPos;
                }
                else if (key == "isDoor") {
                    bool isDoor;
                    iss >> isDoor;
                    cell.isDoor = isDoor;
                }
                else if (key == "isCheckpoint") {
                    bool isCheckpoint;
                    iss >> isCheckpoint;
                    cell.isCheckpoint = isCheckpoint;
                }
                else if (key == "isReadyToRender") {
                    bool isReady;
                    iss >> isReady;
                    cell.isReadyToRender = isReady;
                }
            }

            // After parsing all keys, set positions
            if (xPos != 0.0f || yPos != 0.0f) {
                // Use the loaded positions
                cell.xPos = xPos;
                cell.yPos = yPos;
            } else {
                // Calculate positions based on indices
                cell.xPos = static_cast<float>(col * cellSize);
                cell.yPos = static_cast<float>(row * cellSize);
            }
            // Set the positions of shape and sprite
            cell.shape.setPosition(cell.xPos, cell.yPos);
            cell.sprite.setPosition(cell.xPos, cell.yPos);

            // Initialize shape properties
            cell.shape.setSize(sf::Vector2f(cell.cellSize, cell.cellSize));
            if (cell.cellType == 'C') {
                cell.shape.setFillColor(sf::Color(0, 0, 255, 100)); // Collider color
            } else {
                cell.shape.setFillColor(sf::Color::Transparent);
            }
            cell.shape.setOutlineColor(sf::Color::Red);
            cell.shape.setOutlineThickness(0.5f);
        }
    }

    std::cout << "Successfully loaded section " << sectionIndex << std::endl;
    return true;
}

void Game::init(sf::RenderWindow& window, ResourceManager& resourceManager, Player& player)
{
    player.setPlayerPosition(resourceManager.initalSpawnPositionLevelOne);

    if(!isGameMapLoaded)
    {
        initializeTileTexturesLevelOne();
        
        gameMap = loadGameMap("res/data");
        if (gameMap) {
            std::cout << "Map loaded successfully!\n"
                      << "Screen Map width: " << gameMap->screenWidth << "\n"
                      << "Screen Map height: " << gameMap->screenHeight << "\n"
                      << "Map size: " << gameMap->mapSize << "\n"
                      << "Cell size: " << gameMap->cellSize << "\n"
                      << "Number of sections: " << gameMap->mapSections << std::endl;
            isGameMapLoaded = true;
        } else {
            std::cerr << "Failed to load map!" << std::endl;
        }
    }
    
    sf::View view = window.getDefaultView();
    camera.setSize(1280.0f, 720.0f);
    camera.setCenter(player.shape.getPosition().x - static_cast<float>(window.getSize().x) /2, 0);
    camera.zoom(0.6);

 //   std::cout << "Finished initializing: " << std::endl;
}

void Game::inputHandle()
{
     
}

void Game::update(float deltaTime, Player& player)
{
 //   player.setPlayerPosition(sf::Vector2f(100.0f, 512.0f));
  //  std::cout << "Camera Center: " << camera.getCenter().x << ", " << camera.getCenter().y << std::endl;
 //   std::cout << "Player Position: " << player.shape.getPosition().x << ", " << player.shape.getPosition().y << std::endl;
   // camera.setCenter(player.shape.getPosition());
   // camera.setCenter( player.shape.getPosition().x, player.shape.getPosition().y - 180);
    camera.setCenter( player.shape.getPosition().x, player.shape.getPosition().y - 100);
    
   // calculate position
    // Update player movement first
   // player.onInverseDirection;
    //isFlipedPlayer = false;
    player.handleMovement(deltaTime);
    entityManager.gemUpdate(player);
    
    // Let GEM handle all collisions
 //   entityManager.gemUpdate(player);
    
    // Update camera after final player position is determined
  //  updateCamera(deltaTime, player);
    /*
    const float cameraSmoothing = 0.001f;

    // Get the current camera center and player position
    sf::Vector2f cameraCenter = camera.getCenter();
    sf::Vector2f playerPosition = player.shape.getPosition();

    // Interpolate between the camera center and player position
    cameraCenter.x += (playerPosition.x - cameraCenter.x) * cameraSmoothing;
    cameraCenter.y += (playerPosition.y - cameraCenter.y) * cameraSmoothing;
    

   // camera.setCenter(cameraCenter);
    camera.setCenter(player.shape.getPosition());
    updateBackgroundPosition();*/
}

void Game::draw(sf::RenderWindow& window, ResourceManager& resourceManager) {
    if(!resourceManager.isMainMenuActive)
        window.setView(camera);

    window.draw(resourceManager.backgroundSpriteOne);
    
    // Draw map tiles
    if(gameMap) {
        for(int i = 0; i < gameMap->mapSections; i++) {
            if(gameMap->sections[i]) {
                MapSection* section = gameMap->sections[i];
                int sectionOffsetX = section->mapSectionPositionX;  // Base X position for this section
                
                for(int y = 0; y < section->numberOfCellsPerRow; y++) {
                    for(int x = 0; x < section->numberOfCellsPerRow; x++) {
                        TileCell& cell = section->tilecellArray[y][x];

                        // Calculate the cell position based on section's base position
                        float cellXPos = cell.xPos + sectionOffsetX;
                        float cellYPos = cell.yPos;

                        // Update cell positions with the offset
                        cell.shape.setPosition(cellXPos, cellYPos);
                        cell.sprite.setPosition(cellXPos, cellYPos);
                        
                        // Make all shapes visible with red fill
                        cell.shape.setFillColor(sf::Color(255, 0, 0, 128)); // Semi-transparent red
                        if(cell.cellType == 'C') {
                            window.draw(cell.sprite);
                        }
                    }
                }
            }
        }
    }
    
    window.draw(resourceManager.newGamePlayer.currentSprite);
}
