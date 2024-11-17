#pragma once
#include <string>
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
    void toggleMode();
    void initTileSizeGroup();
    void initGridSizeGroup();
    void initTileMiniViewport();
    void initDebugConsole();
    void initSectionMap();
    void initBrushes();
    void initRotationControls();
    void onSaveButtonClick();
    void initVariablesToSave();
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
    void drawBackground(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow &window);
    void checkMousePOsitionAndClickOnVisibilityAndRotation(const sf::Vector2i& mousePosition, sf::Event event);
    void onLoadButtonClick();
    void checkMousePositionAndClicksLoadSave(const sf::Vector2i& mousePosition, sf::Event event);

    void createTilemap(int tileSizeType);
    void checkMousePositionAndClicksTileSize(const sf::Vector2i& mousePosition, sf::Event event);
    void checkMousePositionAndClicksGridSize(const sf::Vector2i& mousePosition, sf::Event event);
    void changeColorButtonsTileSize();
    void changeColorButtonsGridSize();
    void setBackgroundPosition(sf::Sprite& sprite, int sectionSelected);
    void changeColorButtonsSection();
    void checkMousePositionAndClickOnTileTextures(const sf::Vector2i& mousePosition, sf::Event event);
    void changeColorButtonsTextures();
    void saveCurrentSectionState();
    void checkMousePositionAndClickOnSection(const sf::Vector2i& mousePosition, sf::Event event);
    void checkMousePositionAndClickOnDebugConsole(sf::Vector2i mousePosition, sf::Event event);
    void Update(sf::RenderWindow &window, const sf::Event& event);

    WorldEditor(): tileMapWidth(0), tileMapHeight(0), tileSize(0), gameOverLine(0)
    {
    }
    bool loadButtonClicked = false; 
    bool saveButtonClicked = false;
    
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
 //   void allocateSpritesArrayForMapSection(int screenWidth, int screenHeight, int cellSize);
    void allocateTileCellArray(MapSection* section, int gridSize);
    void deallocateTileCellArray(MapSection* section);
    void saveAndApplyTextureToTile();
    // void deallocateSpritesArray(int rows);
    // draw
    void displayTileSection(sf::RenderWindow &window, MapSection* section);

    // update
  //  void listenChangesInSpriteTilemap();
    // file manager
 //   void loadSpriteTilemap();
 //   void saveSpriteTilemap();
    void setCellSize(int value);
    void displayColliderEncoderArray(sf::RenderWindow& window, MapSection* section);
    void tilemapDraw(sf::RenderWindow& window);
    int getCellSize();

    void tilemapUpdate(sf::RenderWindow &window, const sf::Event& event);
    void checkMousePositionAndClicksWithShift(const sf::Vector2i &mousePosition,  sf::Event event);
    void allocateArrayCharEncoder(TileCell& tilecell);
    void deallocateTileSection(MapSection* section);
    void saveBrushToTile(MapSection* section, int x, int y);
   void applyTextureToTile(MapSection* section, int cellX, int cellY, int textureIndex);
    void initTileTextures();
 
    
    int previousCellSize = 8;

    bool isTextureMode = false;
    int sectionSelected = 1;
private:
    Tilemap tilemap;

    bool canEditCellSize = false;
    GameMap* newGameMap = nullptr;
    MapSection** newMapSection = nullptr;
    int CurrentlySelectedIndex = -1;
    MapSection* currentSection;

  
    static const int NUM_TEXTURES = 18; // 
    sf::String texturesPath[NUM_TEXTURES]  = {
        "res/textures/gameplay/outdoorNight/brickBase.png", // 1
        "res/textures/gameplay/woods/crownPedestal.png",  // 2
         "res/textures/gameplay/outdoorNight/water.png",// 3
        "res/textures/gameplay/woods/comodin.png",// 4
        "res/textures/gameplay/woods/orcHome.png", // 5
        "res/textures/gameplay/cave/caveMiddle.png", // 6
        
        "res/textures/gameplay/outdoorNight/nightoutsidefloorTopEdge.png",// 7
        "res/textures/gameplay/outdoorNight/nightOutsideFloorTop.png", // 8
        "res/textures/gameplay/outdoorNight/brickBaseEdge.png",// 9
        
        "res/textures/gameplay/woods/floorTopWoodsEdge.png",// 10
        "res/textures/gameplay/woods/floorTopWoods.png", // 11
        
        "res/textures/gameplay/cave/doorCave.png", // 12
        
        "res/textures/gameplay/outdoorNight/nightOutsideFloorBaseEdge.png",// 13
        "res/textures/gameplay/outdoorNight/nightOutsideFloorBase.png",     // 14
        "res/textures/gameplay/woods/powerUp.png", // 15

        "res/textures/gameplay/woods/floorCenterWoodsEdge.png", // 16
        "res/textures/gameplay/woods/floorCenterWoods.png", // 17
        
        "res/textures/gameplay/cave/floorCave.png" // 18
    };
    sf::Texture tileTextures[NUM_TEXTURES];
    sf::Sprite tileSprites[NUM_TEXTURES];  

    
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
    sf::Text textTilemap;
    sf::RectangleShape buttonLoad;
    sf::Text buttonTextLoad;
    sf::RectangleShape buttonSave;
    sf::Text buttonTextSave;
    // ------------------------------------------------- Debug Console
    sf::RectangleShape baseDebugConsole;
    sf::Text texDebugConsole;

    std::string consoleInput; // Holds the current text input
    bool isConsoleActive = false;

    sf::Clock debounceClock;
    float debounceDelay = 0.1f; // 100 ms delay
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

    sf::RectangleShape* buttons[18] = {
        &ButtonTextureOne, &ButtonTextureTwo, &ButtonTextureThree, &ButtonTextureFour,
        &ButtonTextureFive, &ButtonTextureSix, &ButtonTextureSeven, &ButtonTextureEight,
        &ButtonTextureNine, &ButtonTextureTen, &ButtonTextureEleven, &ButtonTextureTwelve,
        &ButtonTextureThirteen, &ButtonTextureFourteen, &ButtonTextureFifteen, &ButtonTextureSixteen,
        &ButtonTextureSeventeen, &ButtonTextureEighteen
    };

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

    // -------------------------------------------------- Background Debug




};
