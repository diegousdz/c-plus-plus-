// Tilemap.cpp
#include "Tilemap.h"
#include <iostream>

Tilemap::Tilemap(int type, int cellSize)
{
    tilemapWasCreated = false;
    createTilemapBySize(type, cellSize);
}



Tilemap::~Tilemap()
{
    clearTilemap();
}

void Tilemap::clearTilemap()
{
    std::cout << "Starting clearTilemap()" << std::endl;
    
    if (tilemapSprite != nullptr)
    {
        std::cout << "tilemapSprite is not null, rows = " << rows << std::endl;
        try {
            for (int row = 0; row < rows; row++)
            {
                if (tilemapSprite[row] != nullptr) {
                    std::cout << "Deleting row " << row << std::endl;
                    delete[] tilemapSprite[row];
                    tilemapSprite[row] = nullptr;
                }
            }
            delete[] tilemapSprite;
            tilemapSprite = nullptr;
            std::cout << "Successfully cleared tilemap" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception during clearTilemap: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "tilemapSprite is already null" << std::endl;
    }
    
    // Reset other related variables
    rows = 0;
    cols = 0;
}

sf::Sprite** Tilemap::createTilemapShort(int cellSize)
{
    rows = screenWidth / cellSize;
    cols = sizeShortMap / cellSize;

    tilemapSprite = new sf::Sprite*[rows];
    for (int row = 0; row < rows; row++)
    {
        tilemapSprite[row] = new sf::Sprite[cols];
        for (int col = 0; col < cols; col++)
        {
            tilemapSprite[row][col] = sf::Sprite(); // Initialize each sprite
        }
    }

    tilemapWasCreated = true;
    return tilemapSprite;
}

sf::Sprite** Tilemap::createTilemapMedium(int cellSize)
{
    rows = screenWidth / cellSize;
    cols = sizeMediumMap / cellSize;

    tilemapSprite = new sf::Sprite*[rows];
    for (int row = 0; row < rows; row++)
    {
        tilemapSprite[row] = new sf::Sprite[cols];
        for (int col = 0; col < cols; col++)
        {
            tilemapSprite[row][col] = sf::Sprite();
        }
    }

    tilemapWasCreated = true;
    return tilemapSprite;
}

sf::Sprite** Tilemap::createTilemapLong(int cellSize)
{
    rows = screenWidth / cellSize;
    cols = sizeLongMap / cellSize;

    tilemapSprite = new sf::Sprite*[rows];
    for (int row = 0; row < rows; row++)
    {
        tilemapSprite[row] = new sf::Sprite[cols];
        for (int col = 0; col < cols; col++)
        {
            tilemapSprite[row][col] = sf::Sprite();
        }
    }

    tilemapWasCreated = true;
    return tilemapSprite;
}

sf::Sprite** Tilemap::createTilemapBySize(int type, int cellSize)
{
    switch (type)
    {
    case 1: return createTilemapShort(cellSize);
    case 2: return createTilemapMedium(cellSize);
    case 3: return createTilemapLong(cellSize);
    default: return createTilemapShort(cellSize);
    }
}

sf::Sprite** Tilemap::getTilemap() const
{
    return tilemapSprite;
}

void Tilemap::applyTextureToTile(int x, int y, const sf::Texture& texture) const
{
    if (tilemapSprite != nullptr && y < rows && x < cols)
    {
        tilemapSprite[y][x].setTexture(texture);
    }
}

void Tilemap::deallocateGameMap()
{
    if (gameMap)
    {
        delete gameMap;
        gameMap = nullptr;
        std::cout << "GameMap deallocated." << std::endl;
    }
}

void Tilemap::allocateGameMap(int cellSize, int screenWidth, int screenHeight, int mapSize)
{
    if (gameMap)
        deallocateGameMap();

    gameMap = new GameMap(cellSize, screenWidth, screenHeight, mapSize);
    // Set mapSections based on mapSize
    if (mapSize == 1)
    {
        gameMap->createSections(2);
    }
    else if (mapSize == 2)
    {
        gameMap->createSections(4);
    }
    else if (mapSize == 3)
    {
        gameMap->createSections(6);
    }
    std::cout << "GameMap allocated with cell size: " << cellSize
        << ", screen dimensions: " << screenWidth << "x" << screenHeight
        << ", map size: " << mapSize << std::endl;

    allocateMapSections(gameMap->sections);
}

bool Tilemap::loadTexturePathsFromFile(sf::String textures[], const std::string& configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open())
    {
        std::cerr << "Could not open the config file." << std::endl;
        return false;
    }

    std::string line;
    int index = 0;
    while (std::getline(file, line) && index < 18)
    {
        if (!line.empty())
        {
            textures[index] = sf::String(line); // Store in textures array
            std::cout << "Loaded texture path for button " << index + 1 << ": " << line << std::endl;
        }
        index++;
    }
    file.close();
    return true;
}

void Tilemap::allocateMapSections(MapSection** & sections)
{
    // Clear any existing MapSections if already allocated
    if (gameMap == nullptr)
    {
        std::cerr << "Error: gameMap is null. Please initialize gameMap first." << std::endl;
        return;
    }

    deallocateMapSections();


    int numberOfSections = gameMap->mapSections; // Get the number of sections from gameMap
    if (numberOfSections <= 0)
    {
        std::cerr << "Error: numberOfSections is invalid." << std::endl;
        return;
    }
    // Allocate array for mapSection as an array of MapSection pointers
    sections = new MapSection*[numberOfSections];
    int sectionPosX = 0;
    int sectionWidth = gameMap->screenWidth;

    // Initialize each MapSection with its calculated position
    for (int i = 0; i < numberOfSections; ++i)
    {
        sections[i] = new MapSection(sectionPosX, gameMap->cellSize);
        sectionPosX += sectionWidth;
    }

    // Assign sections to gameMap->sections if it’s not already
    if (gameMap->sections != sections)
    {
        gameMap->sections = sections;
    }
}

void Tilemap::deallocateMapSections()
{
    // Deallocate each MapSection in the array and reset mapSection to nullptr
    if (gameMap && gameMap->sections)
    {
        for (int i = 0; i < gameMap->mapSections; ++i)
        {
            delete gameMap->sections[i];
        }
        delete[] gameMap->sections;
        gameMap->sections = nullptr;
    }
}
