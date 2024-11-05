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
    if (tilemapSprite != nullptr)
    {
        for (int row = 0; row < rows; row++)
        {
            delete[] tilemapSprite[row];
        }
        delete[] tilemapSprite;
        tilemapSprite = nullptr;
    }
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

void Tilemap::applyTextureToTile(int x, int y, const sf::Texture &texture) const
{
    if (tilemapSprite != nullptr && y < rows && x < cols)
    {
        tilemapSprite[y][x].setTexture(texture);
    }
}

void Tilemap::deallocateGameMap() {
    if (gameMap) {
        delete gameMap;
        gameMap = nullptr;
        std::cout << "GameMap deallocated." << std::endl;
    }
}

void Tilemap::allocateGameMap(int cellSize, int screenWidth, int screenHeight, int mapSize)
{
    if(gameMap)
        deallocateGameMap();

    gameMap = new GameMap(cellSize, screenWidth, screenHeight, mapSize);
    std::cout << "GameMap allocated with cell size: " << cellSize 
              << ", screen dimensions: " << screenWidth << "x" << screenHeight 
              << ", map size: " << mapSize << std::endl;
}