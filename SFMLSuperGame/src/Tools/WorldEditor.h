#pragma once
#include <string>

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace std;

class WorldEditor
{
public:

    static WorldEditor& getInstance()
    {
        static WorldEditor instance;
        return instance;
    }
    
    WorldEditor(int screenHeight);


    void init();
    void draw(sf::RenderWindow &window);  // Render editor content
    void Update(sf::RenderWindow &window, sf::Event event);
    void createTilemap(int tileSizeType);

    WorldEditor(): tileMapWidth(0), tileMapHeight(0), tileSize(0), gameOverLine(0)
    {
    }

    int tileMapWidth;
    int tileMapHeight;
    int tileSize;

    int gameAreaPadding = 64;
    
    // Player start position
    int gameStartPositionX = gameAreaPadding;

    //Level end Position achieved
    int gameEndPositionX = -gameAreaPadding;
    
    int gameArea = tileMapWidth - gameAreaPadding * 2;

    int gameOverLine;

    int modules = 0;

    // Fixed Array size
    int modulesPositionX[4] = {0, 0, 0, 0};
    int modulesPositionY[4] = {0, 0, 0, 0};

    // Memory Dynamically Allocated to enable module resize
    int* moduleWidth = new int[4] {0, 0, 0, 0};
    int* moduleHeight = new int[4]{0, 0, 0, 0};
    
    string modulesNames[4] = { "Hierarchy", "Game", "Inspector", "Components"};

    void InitializeGameEditor();
    void ExitGameEditor();
    bool hasCreatedTilemap;
    sf::RenderWindow tileViewPort;
    

private:
    
    sf::RenderWindow editorWindow;  // Editor window for rendering
  
    sf::Font font;  // Font to display text
    sf::Text title;  // Text to show the title

    sf::RectangleShape gridTile;  // Example visual representation of a tile
    int selectedTileType;
    sf::Font fontEditor;
    
    sf::Text titleEditor;
    
    sf::RectangleShape ButtonOne;
    sf::Text ButtonTextOne;

    sf::RectangleShape ButtonTwo;
    sf::Text ButtonTextTwo;

    sf::RectangleShape ButtonThree;
    sf::Text ButtonTextThree;
    
    int tileSizeType = 1;
};
