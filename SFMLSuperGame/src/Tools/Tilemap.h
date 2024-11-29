#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

struct TileCell {
    int cellSize;
    char cellType;
    int textureID;
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture* texture;
    
    float xPos;
    float yPos;
    int spriteRotationAngle;

    bool isDoor;
    bool isCheckpoint;
    bool isReadyToRender;

    TileCell(int size = 8, char type = 'v', int texID = -1, float x = 0.0f, float y = 0.0f) : cellSize(size), cellType(type), textureID(texID), texture(nullptr), xPos(x), yPos(y), spriteRotationAngle(0), isDoor(false), isCheckpoint(false), isReadyToRender(false) {
        shape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
        shape.setPosition(xPos, yPos);
        shape.setFillColor(sf::Color::Transparent);
        sprite.setPosition(xPos, yPos);
    }

    bool saveToFile(const std::string& filePath) const {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: " << filePath << std::endl;
            return false;
        }

        outFile << "cellSize " << cellSize << "\n";
        outFile << "cellType " << cellType << "\n";
        outFile << "textureID " << textureID << "\n";
        outFile << "xPos " << xPos << "\n";
        outFile << "yPos " << yPos << "\n";
        outFile << "spriteRotationAngle " << spriteRotationAngle << "\n";
        outFile << "isDoor " << isDoor << "\n";
        outFile << "isCheckpoint " << isCheckpoint << "\n";
        outFile << "isReadyToRender " << isReadyToRender << "\n";

        outFile << "shapePositionX " << shape.getPosition().x << "\n";
        outFile << "shapePositionY " << shape.getPosition().y << "\n";
        outFile << "shapeSizeX " << shape.getSize().x << "\n";
        outFile << "shapeSizeY " << shape.getSize().y << "\n";

        outFile << "spritePositionX " << sprite.getPosition().x << "\n";
        outFile << "spritePositionY " << sprite.getPosition().y << "\n";
        outFile << "spriteScaleX " << sprite.getScale().x << "\n";
        outFile << "spriteScaleY " << sprite.getScale().y << "\n";
        outFile << "spriteRotationAngle " << sprite.getRotation() << "\n";

        outFile.close();
        std::cout << "TileCell saved to " << filePath << std::endl;
        return true;
    }

    void setCellSize(int newSize) {
        cellSize = newSize;
        shape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    }

    void setCellType(char newType) {
        cellType = newType;
    }
    
    void setTextureID(int newTextureID) {
        textureID = newTextureID;
    }
    
    void setSpriteRotationAngle(int newAngle) {
        spriteRotationAngle = newAngle;
        sprite.setRotation(static_cast<float>(spriteRotationAngle));
    }

    void setIsDoor(bool isDoorValue) {
        isDoor = isDoorValue;
    }

    void setIsCheckpoint(bool isCheckpointValue) {
        isCheckpoint = isCheckpointValue;
    }

    void setIsReadyToRender(bool isReady) {
        isReadyToRender = isReady;
    }

    void setPosition(float x, float y) {
        xPos = x;
        yPos = y;
        shape.setPosition(xPos, yPos);
        sprite.setPosition(xPos, yPos);
    }

    void setTexture(sf::Texture* newTexture) {
        texture = newTexture;
        if (texture) 
            sprite.setTexture(*texture);
    }
};

struct MapSection {
    int mapSectionPositionX = 0;
    int numberOfCellsPerRow = 64;
    TileCell** tilecellArray = nullptr;
    sf::Sprite* backgroundArray = nullptr;

    MapSection(int newMapSectionPositionX, int newNumberOfCellsPerRow) : mapSectionPositionX(newMapSectionPositionX), numberOfCellsPerRow(newNumberOfCellsPerRow) {
        if (numberOfCellsPerRow <= 0) {
            std::cerr << "Invalid number of cells per row: " << numberOfCellsPerRow << std::endl;
            return;
        }

        try {
            tilecellArray = new TileCell*[numberOfCellsPerRow];
            for (int y = 0; y < numberOfCellsPerRow; ++y) {
                tilecellArray[y] = new TileCell[numberOfCellsPerRow];
                for (int x = 0; x < numberOfCellsPerRow; ++x) {
                    tilecellArray[y][x] = TileCell(8, 'v', -1, static_cast<float>(x * 8), static_cast<float>(y * 8));
                    tilecellArray[y][x].shape.setSize(sf::Vector2f(8, 8));
                    tilecellArray[y][x].shape.setPosition(static_cast<float>(x) * 8.0f, static_cast<float>(y) * 8.0f);
                    tilecellArray[y][x].shape.setOutlineColor(sf::Color::Red);
                    tilecellArray[y][x].shape.setOutlineThickness(0.5f);
                    tilecellArray[y][x].shape.setFillColor(sf::Color::Transparent);
                }
            }

            backgroundArray = new sf::Sprite[numberOfCellsPerRow];
            for (int i = 0; i < numberOfCellsPerRow; ++i) {
                backgroundArray[i].setPosition(static_cast<float>(mapSectionPositionX + i * 512), 0.0f);
                backgroundArray[i].setScale(512.0f, 512.0f);
            }
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            if (tilecellArray) {
                for (int y = 0; y < numberOfCellsPerRow; ++y) {
                    delete[] &tilecellArray[y];
                }
                delete[] tilecellArray;
                tilecellArray = nullptr;
            }
            if (backgroundArray) {
                delete[] backgroundArray;
                backgroundArray = nullptr;
            }
        }
    }

    ~MapSection()
    {
        for (int y = 0; y < numberOfCellsPerRow; ++y) {
            delete[] tilecellArray[y];
        }
        delete[] tilecellArray;

        // Clean up backgroundArray
        delete[] backgroundArray;
    }

    bool saveToFile(const std::string& basePath, const std::string& nameFile) const {
        std::string finalPath = basePath + "/" + nameFile + ".dat";

        std::ifstream checkFile(finalPath);
        if (checkFile.is_open()) {
            std::cout << "File already exists: " << finalPath << std::endl;
            checkFile.close();
        } else {
            std::cout << "File does not exist, creating new file: " << finalPath << std::endl;
        }

        std::ofstream outFile(finalPath);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: " << finalPath << std::endl;
            return false;
        }

        outFile << "mapSectionPositionX " << mapSectionPositionX << "\n";
        outFile << "numberOfCellsPerRow " << numberOfCellsPerRow << "\n";
        std::cout << "mapSectionPositionX: " << mapSectionPositionX << std::endl;
        std::cout << "numberOfCellsPerRow: " << numberOfCellsPerRow << std::endl;


        outFile << "tilecellArray:\n";
        for (int y = 0; y < numberOfCellsPerRow; ++y) {
            for (int x = 0; x < numberOfCellsPerRow; ++x) {
                const TileCell& cell = tilecellArray[y][x];
                outFile << "TileCell[" << y << "][" << x << "] "
                        << "cellSize " << cell.cellSize << " "
                        << "cellType " << cell.cellType << " "
                        << "textureID " << cell.textureID << " "
                        << "xPos " << cell.xPos << " "
                        << "yPos " << cell.yPos << " "
                        << "isDoor " << cell.isDoor << " "
                        << "isCheckpoint " << cell.isCheckpoint << " "
                        << "isReadyToRender " << cell.isReadyToRender << "\n";
            }
        }

        outFile << "backgroundArray:\n";
        for (int i = 0; i < 1; ++i) {
            const sf::Sprite& sprite = backgroundArray[i];
            outFile << "Sprite[" << i << "] "
                    << "PositionX " << sprite.getPosition().x << " "
                    << "PositionY " << sprite.getPosition().y << " "
                    << "ScaleX " << sprite.getScale().x << " "
                    << "ScaleY " << sprite.getScale().y << "\n";
        }

        outFile.close();
        std::cout << "Map Section saved to " << finalPath << std::endl;
        return true;
    }
    
    void setNumberOfCellsPerRow(int newNumberOfCellsPerRow) {
        numberOfCellsPerRow = newNumberOfCellsPerRow;
    }

    void setTilecellArray(TileCell** newTilecellArray) {
        tilecellArray = newTilecellArray;
    }

    void setBackgroundArray(sf::Sprite* newBackgroundArray) {
        backgroundArray = newBackgroundArray;
    }

    bool loadFromFile(const char* basePath, const std::string& fileName) {
        std::string filePath = std::string(basePath) + "/" + fileName + ".dat";
        std::ifstream inFile(filePath);

        if (inFile.is_open()) {
            std::string line, key;
            while (std::getline(inFile, line)) {
                std::istringstream iss(line);
                iss >> key;

                if (key == "mapSectionPositionX") {
                    iss >> mapSectionPositionX;
                } else if (key == "numberOfCellsPerRow") {
                    iss >> numberOfCellsPerRow;
                } else if (key.find("TileCell[") != std::string::npos) {
                    int row, col;
                    sscanf_s(key.c_str(), "TileCell[%d][%d]", &row, &col);
                
                    std::string cellKey;
                    while (iss >> cellKey) {
                        if (cellKey == "cellSize") {
                            iss >> tilecellArray[row][col].cellSize;
                        } else if (cellKey == "cellType") {
                            iss >> tilecellArray[row][col].cellType;
                        } else if (cellKey == "textureID") {
                            iss >> tilecellArray[row][col].textureID;
                        } else if (cellKey == "xPos") {
                            iss >> tilecellArray[row][col].xPos;
                        } else if (cellKey == "yPos") {
                            iss >> tilecellArray[row][col].yPos;
                        } else if (cellKey == "isDoor") {
                            iss >> tilecellArray[row][col].isDoor;
                        } else if (cellKey == "isCheckpoint") {
                            iss >> tilecellArray[row][col].isCheckpoint;
                        } else if (cellKey == "isReadyToRender") {
                            iss >> tilecellArray[row][col].isReadyToRender;
                        }
                    }

                    if (tilecellArray[row][col].textureID >= 0) {
                        tilecellArray[row][col].shape.setPosition(tilecellArray[row][col].xPos, tilecellArray[row][col].yPos);
                        tilecellArray[row][col].sprite.setPosition(tilecellArray[row][col].xPos, tilecellArray[row][col].yPos);
                    }
                }
            }

            inFile.close();
            std::cout << "MapSection loaded from " << filePath << std::endl;
            std::cout << "Loaded values: position=" << mapSectionPositionX << ", cells per row=" << numberOfCellsPerRow << std::endl;
            return true;
        } else {
            std::cerr << "Failed to open file for loading: " << filePath << std::endl;
            return false;
        }
    }
};

struct GameMap {
    int cellSize = 8;
    int screenWidth = 512;
    int screenHeight = 512;
    int mapSize = 2;
    sf::String texturesPath[18];
    
    int mapSections = 0;
    MapSection** sections = nullptr;

    GameMap(int cellSize = 8, int screenWidth = 512, int screenHeight = 512, int mapSize = 1) : cellSize(cellSize), screenWidth(screenWidth), screenHeight(screenHeight), mapSize(mapSize) {
        if(mapSize == 1) {
            mapSections = 2;
        }
        if(mapSize == 2) {
            mapSections = 4;
        }
        if(mapSize == 3) {
            mapSections = 6;
        }

        for (int i = 0; i < 18; ++i) {
            texturesPath[i] = "none";  
        }
    }
    void clearSections() {
       
        if (sections) {
            for (int i = 0; i < mapSections; ++i) {
                delete sections[i];
            }
            delete[] sections;
            sections = nullptr;
            mapSections = 0;
        }
    }
    
    void createSections(int numberOfSections) {
        clearSections();

        mapSections = numberOfSections;
        sections = new MapSection*[mapSections];
        
        int sectionPosX = 0;
        int numberOfCellsPerRow = screenWidth / cellSize;
    
        std::cout << "Creating " << numberOfSections << " sections with " << numberOfCellsPerRow << " cells per row" << std::endl;
    
        for (int i = 0; i < numberOfSections; ++i) {
            try {
                sections[i] = new MapSection(sectionPosX, numberOfCellsPerRow);
                if (sections[i]) {
                    std::cout << "Section " << i << " initialized at position " << sectionPosX << std::endl;
                } else {
                    std::cerr << "Failed to initialize Section " << i << std::endl;
                }
                sectionPosX += screenWidth;  // Move to next section position
            } catch (const std::exception& e) {
                std::cerr << "Error creating section " << i << ": " << e.what() << std::endl;
                sections[i] = nullptr;
            }
        }
    }
    
    bool saveToFile(const std::string& basePath, const std::string& nameFile) const {
        std::string finalPath = basePath + "/" + nameFile + ".dat";

        std::ifstream checkFile(finalPath);
        if (checkFile.is_open()) {
            std::cout << "File already exists: " << finalPath << std::endl;
            checkFile.close();
        } else {
            std::cout << "File does not exist, creating new file: " << finalPath << std::endl;
        }

        std::ofstream outFile(finalPath);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: " << finalPath << std::endl;
            return false;
        }

        outFile << "cellSize " << cellSize << "\n";
        outFile << "screenWidth " << screenWidth << "\n";
        outFile << "screenHeight " << screenHeight << "\n";
        outFile << "mapSize " << mapSize << "\n";
        outFile << "mapSections " << mapSections << "\n";

        for (int i = 0; i < 18; ++i) {
            outFile << "texturePath" << i << " " << texturesPath[i].toAnsiString() << "\n";
        }
        outFile.close();
        std::cout << "GameMap saved to " << finalPath << std::endl;
        return true;
    }
    
    void setCellSize(int newCellSize) {
        cellSize = newCellSize;
        std::cout << cellSize << std::endl;
    }

    void setScreenWidth(int newScreenWidth) {
        screenWidth = newScreenWidth;
    }

    void setScreenHeight(int newScreenHeight) {
        screenHeight = newScreenHeight;
    }

    void setMapSize(int newMapSize) {
        mapSize = newMapSize;
    }

    void setMapSections(int newMapSections) {
        mapSections = newMapSections;
        std::cout << "Map sections updated to: " << mapSections << std::endl;
    }

    void setTexturePath(int index, const sf::String& newPath) {
        if (index >= 0 && index < 18) {
            texturesPath[index] = newPath;
        } else {
            std::cout << "Index out of bounds for texturesPath array!" << std::endl;
        }
    }
    
    ~GameMap() {
        clearSections(); 
    }

   
    bool loadFromFile(const char* basePath, const char* fileName) {
        std::string filePath = std::string(basePath) + "/" + std::string(fileName) + ".dat";
        std::ifstream inFile(filePath);

        if (inFile.is_open()) {
            inFile >> cellSize;
            inFile >> screenWidth;
            inFile >> screenHeight;
            inFile >> mapSize;
            inFile >> mapSections;

            for (int i = 0; i < 18; i++) {
                std::string path;
                inFile >> path;
                texturesPath[i] = path;
            }

            inFile.close();
            std::cout << "GameMap loaded from " << filePath << std::endl;
            std::cout << "Loaded values: cellSize=" << cellSize 
                      << ", screenWidth=" << screenWidth 
                      << ", screenHeight=" << screenHeight 
                      << ", mapSize=" << mapSize 
                      << ", mapSections=" << mapSections << std::endl;
            return true;
        } else {
            std::cerr << "Failed to open file for loading: " << filePath << std::endl;
            return false;
        }
    }
};

class Tilemap {
public:
    Tilemap(int type = 1, int cellSize = 32); 
    ~Tilemap();
    
    sf::Sprite** createTilemapShort(int cellSize);
    sf::Sprite** createTilemapMedium(int cellSize);
    sf::Sprite** createTilemapLong(int cellSize); 
    sf::Sprite** createTilemapBySize(int type, int cellSize);
    sf::Sprite** tilemapSprite = nullptr;
    sf::Sprite** getTilemap() const;

    GameMap* getGameMap() { return gameMap;}
    GameMap* gameMap = nullptr;
    MapSection** getMapSection() const { return mapSection; }
    MapSection** mapSection = nullptr;
    TileCell** tileCellArray = nullptr;
    
    int rows;
    int cols;
    int screenWidth = 512;
    int sizeShortMap = 1024;
    int sizeMediumMap = 2048;
    int sizeLongMap = 3072;
    bool tilemapWasCreated;
    
    void clearTilemap();
    void applyTextureToTile(int x, int y, const sf::Texture& texture) const;
    
    void allocateGameMap(int cellSize, int screenWidth, int screenHeight, int mapSize);
    void deallocateGameMap();

    void allocateMapSections(MapSection** &sections);
    void deallocateMapSections();
    bool loadTexturePathsFromFile(sf::String textures[] ,const std::string& configPath);
};