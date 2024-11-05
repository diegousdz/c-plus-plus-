#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>

// TileCell.h
#pragma once
#include <SFML/Graphics.hpp>

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
    int tileCurrentRotationAngle;

    bool isDoor;
    bool isCheckpoint;
    bool isReadyToRender;

    TileCell(int size = 8, char type = 'v', int texID = -1, float x = 0.0f, float y = 0.0f)
        : cellSize(size), cellType(type), textureID(texID), texture(nullptr),
          xPos(x), yPos(y), tileCurrentRotationAngle(0),
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

};
