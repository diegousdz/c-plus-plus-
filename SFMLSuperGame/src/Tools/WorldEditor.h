#pragma once
#include <string>

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tilemap.h"

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
    void initTileSizeGroup();
    void initGridSizeGroup();
    void initTileMiniViewport();
    void initDebugConsole();
    void initSectionMap();
    void initBrushes();
    void initRotationControls();
    void initLoadTilemap();
    void init();
    
    void drawTileSizeGroup(sf::RenderWindow &window) const;
    void drawTileGridGroup(sf::RenderWindow& window) const;
    void drawTileMiniViewport(sf::RenderWindow& window) const;
    void drawTileLoadTilemap(sf::RenderWindow& window) const;
    void drawDebugConsole(sf::RenderWindow& window) const;
    void drawSectionMap(sf::RenderWindow& window) const;
    void drawBrushesTexture(sf::RenderWindow& window);
    void drawRotationControls(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow &window);
    
    void createTilemap(int tileSizeType);
    void checkMousePositionAndClicksTileSize(const sf::Vector2i& mousePosition, sf::Event event);
    void checkMousePositionAndClicksGridSize(const sf::Vector2i& mousePosition, sf::Event event);
    void changeColorButtonsTileSize();
    void changeColorButtonsGridSize();
    void changeColorButtonsSection();
    void checkMousePositionAndClickOnSection(const sf::Vector2i& mousePosition, sf::Event event);
    void Update(sf::RenderWindow &window, const sf::Event& event);

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
    bool hasCreatedTilemap;
    sf::RenderWindow tileViewPort;
    
    // init
    void allocateSpritesArrayForMapSection(int screenWidth, int screenHeight, int cellSize);
    void deallocateSpritesArray(int rows);
    // draw
    void displaySpritesArray(sf::RenderWindow &window);

    // update
  //  void listenChangesInSpriteTilemap();
    // file manager
 //   void loadSpriteTilemap();
 //   void saveSpriteTilemap();
    void setCellSize(int value);
    void displayColliderEncoderArray(sf::RenderWindow& window);
    void tilemapDraw(sf::RenderWindow& window);
    int getCellSize();
    bool hasAllocatedSpritesAndShapes = false;

    void tilemapUpdate(sf::RenderWindow &window, const sf::Event& event);
    void checkMousePositionAndClicksWithShift(const sf::Vector2i &mousePosition,  sf::Event event);
    void allocateArrayCharEncoder(int rows, int cols);
    void deallocateArrayCharEncoder(int rows);
    int previousCellSize = 8;

private:
    Tilemap tilemap;
    
    sf::Sprite** spriteArrayTilemap = nullptr;
    sf::RectangleShape** colliderArray = nullptr;
    char** ArrayCharEncoder = nullptr;
    int** textureIDArray = nullptr;
    
    int rowsOfSprites;
    int numberOfCellsPerRow;
    
    sf::Vector2i mousePosition;
    sf::RenderWindow editorWindow;  // Editor window for rendering
    sf::Font font;  // Font to display text
    sf::RectangleShape gridTile;  // Example visual representation of a tile
    // ------------------------------------------------- Tile Size
    sf::RectangleShape TileSizeBaseSection;
    sf::Text title;  // Text to show the title
    sf::Font fontEditor;
    sf::Text titleEditor;
    sf::RectangleShape buttonOneFileSize;
    sf::Text buttonTextOneFileSize;
    sf::RectangleShape buttonTwoFileSize;
    sf::Text buttonTextTwoFileSize;
    sf::RectangleShape buttonThreeFileSize;
    sf::Text buttonTextThreeFileSize;
    int tileSizeType = 1;
    // ------------------------------------------------- Grid Size 
    sf::Text titleGrid;  // Text to show the title
    sf::RectangleShape ButtonOneGrid;
    sf::Text ButtonTextOneGrid;
    sf::RectangleShape ButtonTwoGrid;
    sf::Text ButtonTextTwoGrid;
    sf::RectangleShape ButtonThreeGrid;
    sf::Text ButtonTextThreeGrid;
    int gridSizeType = 1;
    // ------------------------------------------------- Tile Mini-Viewport
    sf::RectangleShape miniViewportBaseTile;
    sf::RectangleShape gamePreview;
    sf::RectangleShape topHeader;
    sf::RectangleShape magicBelt;
    // ------------------------------------------------- Load Tilemap
    sf::RectangleShape baseLoadTilemap;
    sf::Text instructionLoadTilemap;
    sf::RectangleShape buttonLoadTilemap;
    sf::Text buttonTextLoadTile;
    sf::RectangleShape buttonSaveTilemap;
    sf::Text buttonTextSaveTilemap;
    // ------------------------------------------------- Debug Console
    sf::RectangleShape baseDebugConsole;
    sf::Text texDebugConsole;
    // ------------------------------------------------- Sizes for math
    float sectionLoadTilemapHeight;
    float sectionTileSizeHeight;
    // ------------------------------------------------- Current Section Map Selected

    sf::Text titleSection;  // Text to show the title
    sf::RectangleShape ButtonSectionOne;
    sf::RectangleShape ButtonSectionTwo;
    sf::RectangleShape ButtonSectionThree;
    sf::RectangleShape ButtonSectionFour;
    sf::RectangleShape ButtonSectionFive;
    sf::RectangleShape ButtonSectionSix;
    int sectionSelected = 1;
    
    // ------------------------------------------------- Brush Textures
    sf::Text titleBrushed;

    // First row of texture buttons
    sf::RectangleShape ButtonTextureOne;
    sf::RectangleShape ButtonTextureTwo;
    sf::RectangleShape ButtonTextureThree;
    sf::RectangleShape ButtonTextureFour;
    sf::RectangleShape ButtonTextureFive;
    sf::RectangleShape ButtonTextureSix;

    // Second row of texture buttons
    sf::RectangleShape ButtonTextureSeven;
    sf::RectangleShape ButtonTextureEight;
    sf::RectangleShape ButtonTextureNine;
    sf::RectangleShape ButtonTextureTen;
    sf::RectangleShape ButtonTextureEleven;
    sf::RectangleShape ButtonTextureTwelve;

    // Third row of texture buttons
    sf::RectangleShape ButtonTextureThirteen;
    sf::RectangleShape ButtonTextureFourteen;
    sf::RectangleShape ButtonTextureFifteen;
    sf::RectangleShape ButtonTextureSixteen;
    sf::RectangleShape ButtonTextureSeventeen;
    sf::RectangleShape ButtonTextureEighteen;

    // ------------------------------------------------- Sprite Rotation
    sf::Text titleRotation;

    sf::Text titleRotationLeft;
    sf::RectangleShape ButtonRotateOne;
    sf::Text titleRotationRight;
    sf::RectangleShape ButtonRotateTwo;
    sf::Text titleRotationTop;
    sf::RectangleShape ButtonRotateThree;
    sf::Text titleRotationBottom;
    sf::RectangleShape ButtonRotateFour;

};
