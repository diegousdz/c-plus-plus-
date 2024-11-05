#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>

// TileCell.h
#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

struct GameMap
{
    int cellSize = 8;
    int screenWidth = 512;
    int screenHeight = 512;
    
    int mapSize = 1;

    // array of strings with defined size of 18 total indexes, with a fixed size of 18 
    sf::String texturesPath[18];
    
    int mapSections = 0;

    GameMap(int cellSize = 8, int screenWidth = 512, int screenHeight = 512, int mapSize = 1) : cellSize(cellSize), screenWidth(screenWidth), screenHeight(screenHeight), mapSize(mapSize)
    {
        for (int i = 0; i < 18; ++i) {
            texturesPath[i] = "none";  // or a unique name like "default_texture_" + std::to_string(i)
        }
    }

    bool saveToFile(const std::string& basePath, const std::string& nameFile) const {
        // Construct the file path with .dat extension
        std::string finalPath = basePath + "/" + nameFile + ".dat";

        // Check if the file already exists
        std::ifstream checkFile(finalPath);
        if (checkFile.is_open()) {
            std::cout << "File already exists: " << finalPath << std::endl;
            checkFile.close();
        } else {
            std::cout << "File does not exist, creating new file: " << finalPath << std::endl;
        }

        // Open the file for writing
        std::ofstream outFile(finalPath);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: " << finalPath << std::endl;
            return false;
        }

        // Write properties to file
        outFile << "cellSize " << cellSize << "\n";
        outFile << "screenWidth " << screenWidth << "\n";
        outFile << "screenHeight " << screenHeight << "\n";
        outFile << "mapSize " << mapSize << "\n";
        outFile << "mapSections " << mapSections << "\n";

        // Save textures paths
        for (int i = 0; i < 18; ++i) {
            outFile << "texturePath" << i << " " << texturesPath[i].toAnsiString() << "\n";
        }

        // Close the file after saving
        outFile.close();
        std::cout << "GameMap saved to " << finalPath << std::endl;
        return true;
    }
    
    void setCellSize(int newCellSize) {
        cellSize = newCellSize;
    }

    // Setter for screenWidth
    void setScreenWidth(int newScreenWidth) {
        screenWidth = newScreenWidth;
    }

    // Setter for screenHeight
    void setScreenHeight(int newScreenHeight) {
        screenHeight = newScreenHeight;
    }

    // Setter for mapSize
    void setMapSize(int newMapSize) {
        mapSize = newMapSize;
    }

    // Setter for mapSections
    void setMapSections(int newMapSections) {
        mapSections = newMapSections;
    }

    // Setter for texturesPath at a specific index
    void setTexturePath(int index, const sf::String& newPath) {
        if (index >= 0 && index < 18) {
            texturesPath[index] = newPath;
        } else {
            std::cout << "Index out of bounds for texturesPath array!" << std::endl;
        }
    }

    
};
struct TileCell
{
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

    TileCell(int size = 8, char type = 'v', int texID = -1, float x = 0.0f, float y = 0.0f)
        : cellSize(size), cellType(type), textureID(texID), texture(nullptr),
          xPos(x), yPos(y), spriteRotationAngle(0),
          isDoor(false), isCheckpoint(false), isReadyToRender(false)
    {
        shape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
        shape.setPosition(xPos, yPos);
        shape.setFillColor(sf::Color::Transparent);
        sprite.setPosition(xPos, yPos);
    }

    void setTexture(sf::Texture* newTexture) {
        texture = newTexture;
        if (texture) {
            sprite.setTexture(*texture);
        }
    }

    void setPosition(float x, float y) {
        xPos = x;
        yPos = y;
        shape.setPosition(xPos, yPos);
        sprite.setPosition(xPos, yPos);
    }
};
struct MapSection
{
    int numberOfCellsPerRow = 64;
    TileCell** tilecellArray = new TileCell*[numberOfCellsPerRow];
    sf::Sprite** spriteArrayTilemap = nullptr;
};

class Tilemap
{
public:
    
    Tilemap(int type = 1, int cellSize = 32); // Constructor
    ~Tilemap(); // Destructor
    
    void clearTilemap();
    
    sf::Sprite** createTilemapShort(int cellSize);
    sf::Sprite** createTilemapMedium(int cellSize);
    sf::Sprite** createTilemapLong(int cellSize); 

    sf::Sprite** createTilemapBySize(int type, int cellSize);
    sf::Sprite** tilemapSprite = nullptr;

    sf::Sprite** getTilemap() const;

    void applyTextureToTile(int x, int y, const sf::Texture& texture) const;
    
    int rows;
    int cols;
    
    int screenWidth = 512;
    
    int sizeShortMap = 1024;
    int sizeMediumMap = 2048;
    int sizeLongMap = 3072;

    bool tilemapWasCreated;

    TileCell** tileCellArray = nullptr;

    // --------------- map

    void allocateGameMap(int cellSize, int screenWidth, int screenHeight, int mapSize);
    void deallocateGameMap();
    
    GameMap* getGameMap() { return gameMap;}
    GameMap* gameMap = nullptr;
};
