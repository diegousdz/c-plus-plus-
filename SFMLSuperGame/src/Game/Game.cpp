#include "Game.h"
#include "./../Core/ResourceManager.h"
#include "../GameEntities/Orc.h"


Game::Game()
{
    
}

float Game::recalculateYPositionOfDoor(int row)
{
    if(row == 15)
    {
        return 32;
    } else if(row == 14)
    {
        return 64;
    } else if(row == 13)
    {
        return 96;
    } else if(row == 12)
    {
        return 128;
    } else if(row == 11)
    {
        return 160;
    } else if(row == 10)
    {
        return 192;
    } else if(row == 9)
    {
        return 224;
    } else if(row == 8)
    {
        return 256;
    } else if(row == 7)
    {
        return 288;
    } else if(row == 6)
    {
        return 320;
    } else if(row == 5)
    {
        return 352;
    } else if(row == 4)
    {
        return 384;
    } else if(row == 3)
    {
        return 416;
    } else if(row == 2)
    {
        return 448;
    }
    else if(row == 1)
    {
        return 480;
    } else if(row == 0)
    {
        return 512;
    } 
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

GameMap* Game::loadGameMap(const std::string& basePath, int playerLevel)
{
    std::string mapPath;
    if(playerLevel == 1)
    {
        mapPath = basePath + "/mapLevel_One/gameMap.dat";
        std::cout << mapPath << std::endl;
       // std::cout << mapPath;
    } else if (playerLevel == 2)
    {
        mapPath = basePath + "/mapLevel_Two/gameMap.dat";
    } else
    {
        mapPath = basePath + "/mapLevel_Three/gameMap.dat";
    }
    
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
            for (int i = 0; i < NUM_LEVEL_TEXTURES; i++) {
                if (texturesPathlevelOne[i] != "none") {
                    if (!tileTexturesLevelOne[i].loadFromFile(texturesPathlevelOne[i])) {
                        std::cerr << "Failed to load texture: " << texturesPathlevelOne[i].toAnsiString() << std::endl;
                    }
                }
            }
            
            // Load each map section
            for (int i = 0; i < mapSections; i++) {
                loadMapSection(gameMap, basePath, i, tileTexturesLevelOne, playerLevel);
            }
            
            std::cout << "Game map loaded successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to open game map file: " << mapPath << std::endl;
    }

    return gameMap;
}

bool Game::loadMapSection(GameMap* gameMap, const std::string& basePath, int sectionIndex, sf::Texture* textures, int playerLevel) {
    std::string sectionPath;

    if(playerLevel == 1)
    {
        sectionPath = basePath + "/mapLevel_One/mapSection_" + std::to_string(sectionIndex) + ".dat";
    } else if (playerLevel == 2)
    {
        sectionPath = basePath + "/mapLevel_Two/mapSection_" + std::to_string(sectionIndex) + ".dat";
    } else
    {
        sectionPath = basePath + "/mapLevel_Three/mapSection_" + std::to_string(sectionIndex) + ".dat";
    }

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
            iss >> temp; 
            
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

                    // Check if this tile is a door
                    if (isDoor) {
                        // Calculate pixel position using row, col, and cellSize
                        int offsetMap = (mapSectionNumberWhereDoorIsAtLevelOne - 1) * 512;
                        float doorX = static_cast<float>(col * cellSize);
                        doorX = doorX + offsetMap;
                
                        float doorY = recalculateYPositionOfDoor(row);


                        // Print the position of the door tile
                        std::cout << "Door Tile Position - X: " << doorX << ", Y: " << doorY << std::endl;

                        // Save the position if required (example variables)
                        this->doorLevelOnePosX = doorX;
                        this->doorLevelOnePosY = doorY;
                    }
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
                if(cell.cellType == 'V' && cell.textureID == 11 || cell.cellType == 'V' && cell.textureID == 2)
                {
                    cell.shape.setFillColor(sf::Color(0, 0, 255, 100));
                }
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
    resourceManager.allocateEnemies();
    //resourceManager.repositionEnemiesLevelOne(64.0f, 356.0f);
    resourceManager.createEnemiesLevelOne(64.0f, 356.0f);

    if(!isGameMapLoaded)
    {
        initializeTileTexturesLevelOne();
        
        gameMap = loadGameMap("res/data", 1);
        if (gameMap) {
            std::cout << "Map loaded successfully!\n"
                      << "Screen Map width: " << gameMap->screenWidth << "\n"
                      << "Screen Map height: " << gameMap->screenHeight << "\n"
                      << "Map size: " << gameMap->mapSize << "\n"
                      << "Cell size: " << gameMap->cellSize << "\n"
                      << "Number of sections: " << gameMap->mapSections << std::endl;
            isGameMapLoaded = true;
        } else {
            std::cerr << "Load game!" << std::endl;
        }
    }
    
    sf::View view = window.getDefaultView();
    camera.setSize(1280.0f, 720.0f);
    camera.setCenter(player.shape.getPosition().x - static_cast<float>(window.getSize().x) /2, 0);
    camera.zoom(static_cast<float>(0.6));
}

void Game::checkForDoorsAndWinCondition(Player& player)
{
  
    if(playerCurrentLevel == 1)
    {
        if(player.shape.getPosition().x > doorLevelOnePosX)
        {
            if(winLevel == playerCurrentLevel)
            {
                std::cout << "Player wins Level!" << std::endl;
                std::cout << "Player X: " << player.shape.getPosition().x
                << ", Door X: " << doorLevelOnePosX
                << ", Player Level: " << playerCurrentLevel
                << ", Win Level: " << winLevel << std::endl;
            } else
            {
                if(playerCurrentLevel != 2)
                    // load LeveL and pasas the number off level as a parameter
                        playerCurrentLevel = 2;
            }
        }
    } else if (playerCurrentLevel == 2)
    {
        if(player.shape.getPosition().x > doorLevelTwoPosX)
        {
            if(winLevel == playerCurrentLevel)
            {
                std::cout << "Player wins Level!" << std::endl;

                std::cout << "Player wins Level!" << std::endl;
                std::cout << "Player X: " << player.shape.getPosition().x
                << ", Door X: " << doorLevelOnePosX
                << ", Player Level: " << playerCurrentLevel
                << ", Win Level: " << winLevel << std::endl;
            } else
            {
                if(playerCurrentLevel != 3)
                    // load LeveL and pasas the number off level as a parameter
                        playerCurrentLevel = 3;
            }
        }
    } else
    {
        // adjust to check if user is grabbing to grab..
        if(player.shape.getPosition().x > doorLevelThreePosX)
        {
            if(winLevel == playerCurrentLevel)
            {
                // display win screen
                std::cout << "Player wins Level!" << std::endl;
                std::cout << "Player wins Level!" << std::endl;
                std::cout << "Player X: " << player.shape.getPosition().x
                << ", Door X: " << doorLevelOnePosX
                << ", Player Level: " << playerCurrentLevel
                << ", Win Level: " << winLevel << std::endl;
            }
        }
    }

}
void Game::update(float deltaTime, Player& player)
{





    camera.setCenter( player.shape.getPosition().x, player.shape.getPosition().y - 100);
    player.handleMovement(deltaTime);
    entityManager.gemUpdate(player, collisionCells);
    checkForDoorsAndWinCondition(player);
}

void Game::draw(sf::RenderWindow& window, ResourceManager& resourceManager) {
    if(!resourceManager.isMainMenuActive)
        window.setView(camera);

    window.draw(resourceManager.backgroundSpriteOne);
    
    if(gameMap) {
        if(resourceManager.hasSpawnOneInitialized)
        {
            for(int i = 0; i < 5; i++)
            {
                window.draw(resourceManager.orcSpawnManagerOne[i]->shape);
            }
            
        }
        for(int i = 0; i < gameMap->mapSections; i++) {
            if(gameMap->sections[i]) {
                MapSection* section = gameMap->sections[i];
                int sectionOffsetX = section->mapSectionPositionX; 
                
                for(int y = 0; y < section->numberOfCellsPerRow; y++) {
                    for(int x = 0; x < section->numberOfCellsPerRow; x++) {
                        TileCell& cell = section->tilecellArray[y][x];
                        
                        float cellXPos = cell.xPos + sectionOffsetX;
                        float cellYPos = cell.yPos;
                        
                        cell.shape.setPosition(cellXPos, cellYPos);
                        cell.sprite.setPosition(cellXPos, cellYPos);
                        
                        if(cell.cellType == 'C') {
                            
                            collisionCells.push_back(&cell);
                            
                            window.draw(cell.sprite);
                        }
                        if(cell.cellType == 'V' && cell.textureID == 11 || cell.cellType == 'V' && cell.textureID == 2)
                        {
                            window.draw(cell.sprite);
                        }

                        if(!cell.textureID == -1)
                        {
                         
                             window.draw(cell.shape);
                        }
                    }
                }
            }
        }
    }
    
    window.draw(resourceManager.newGamePlayer.currentSpritePlayer);
    window.draw(resourceManager.newGamePlayer.shape);
    
}

void Game::restartGame(Player& player, ResourceManager& resourceManager)
{
    player.setPlayerPosition(resourceManager.initalSpawnPositionLevelOne);

    player.velocity = sf::Vector2f(0.0f, 0.0f);
    player.isOnGround = false;
    player.isMoving = false;
    player.onInverseDirection = false;
  
    player.currentSpritePlayer.setPosition(resourceManager.initalSpawnPositionLevelOne);
    player.shape.setPosition(resourceManager.initalSpawnPositionLevelOne);
    
    camera.setCenter(player.shape.getPosition().x, player.shape.getPosition().y - 100);
    
    player.updateAnimation(0); // Reset animation frame
    
    collisionCells.clear();

    resourceManager.gameOver = false;
    resourceManager.gameOverInitialized = false;
    resourceManager.isMainMenuActive = true;

    // Reload the game map if necessary
    // If your game map can change during gameplay, you might need to reload it here
    // For simplicity, we assume the map remains the same

    // Reset any other game-specific variables
    // For example, reset score, enemy positions, etc.
    // Since your game is simple for now, this might not be necessary

    // Debug message
    std::cout << "Game has been restarted." << std::endl;
}
