#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Tilemap.h"

using namespace std;

class WorldEditor {
public:
    static WorldEditor& getInstance() {
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
    void drawBrushesTexture(sf::RenderWindow& window) const;
    void drawRotationControls(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow &window);
    void checkMousePositionAndClickOnVisibilityAndRotation(const sf::Vector2i& mousePosition, sf::Event event);
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

    WorldEditor(): tileMapWidth(0), tileMapHeight(0), tileSize(0), gameOverLine(0) {}
    
    bool loadButtonClicked = false; 
    bool saveButtonClicked = false;
    
    int tileMapWidth;
    int tileMapHeight;
    int tileSize;
    int gameAreaPadding = 64;
    int gameStartPositionX = gameAreaPadding;
    int gameEndPositionX = -gameAreaPadding;
    int gameArea = tileMapWidth - gameAreaPadding * 2;
    int gameOverLine;
    int modules = 0;
    bool hasCreatedTilemap;
    sf::RenderWindow tileViewPort;

    void allocateTileCellArray(MapSection* section, int gridSize);
    void deallocateTileCellArray(MapSection* section);
    void saveAndApplyTextureToTile();
    void displayTileSection(sf::RenderWindow &window, MapSection* section);
    void setCellSize(int value);
    void displayColliderEncoderArray(sf::RenderWindow& window, MapSection* section);
    void tilemapDraw(sf::RenderWindow& window);
    int getCellSize();

    void tilemapUpdate(sf::RenderWindow &window, const sf::Event& event);
    void checkMousePositionAndClicksWithShift(const sf::Vector2i &mousePosition, sf::Event event);
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

    static const int NUM_TEXTURES = 18;
    sf::String texturesPath[NUM_TEXTURES] = {
        "res/textures/gameplay/outdoorNight/brickBase.png",
        "res/textures/gameplay/woods/crownPedestal.png",
        "res/textures/gameplay/outdoorNight/water.png",
        "res/textures/gameplay/woods/comodin.png",
        "res/textures/gameplay/woods/orcHome.png",
        "res/textures/gameplay/cave/caveMiddle.png",
        "res/textures/gameplay/outdoorNight/nightoutsidefloorTopEdge.png",
        "res/textures/gameplay/outdoorNight/nightOutsideFloorTop.png",
        "res/textures/gameplay/outdoorNight/brickBaseEdge.png",
        "res/textures/gameplay/woods/floorTopWoodsEdge.png",
        "res/textures/gameplay/woods/floorTopWoods.png",
        "res/textures/gameplay/cave/doorCave.png",
        "res/textures/gameplay/outdoorNight/nightOutsideFloorBaseEdge.png",
        "res/textures/gameplay/outdoorNight/nightOutsideFloorBase.png",
        "res/textures/gameplay/woods/powerUp.png",
        "res/textures/gameplay/woods/floorCenterWoodsEdge.png",
        "res/textures/gameplay/woods/floorCenterWoods.png",
        "res/textures/gameplay/cave/floorCave.png"
    };
    
    sf::Texture tileTextures[NUM_TEXTURES];
    sf::Sprite tileSprites[NUM_TEXTURES];  
    sf::Vector2i mousePosition;
    sf::RenderWindow editorWindow;
    sf::Font font;
    sf::RectangleShape gridTile;
    sf::RectangleShape TileSizeBaseSection;
    sf::Text title;
    sf::Font fontEditor;
    sf::Text titleEditor;
    sf::RectangleShape buttonOneFileSize;
    sf::Text buttonTextOneFileSize;
    sf::RectangleShape buttonTwoFileSize;
    sf::Text buttonTextTwoFileSize;
    sf::RectangleShape buttonThreeFileSize;
    sf::Text buttonTextThreeFileSize;
    int tileSizeType = 1;
    sf::Text titleGrid;
    sf::RectangleShape ButtonOneGrid;
    sf::Text ButtonTextOneGrid;
    sf::RectangleShape ButtonTwoGrid;
    sf::Text ButtonTextTwoGrid;
    sf::RectangleShape ButtonThreeGrid;
    sf::Text ButtonTextThreeGrid;
    int gridSizeType = 1;
    sf::RectangleShape miniViewportBaseTile;
    sf::RectangleShape gamePreview;
    sf::RectangleShape topHeader;
    sf::RectangleShape magicBelt;
    sf::RectangleShape baseLoadTilemap;
    sf::Text textTilemap;
    sf::RectangleShape buttonLoad;
    sf::Text buttonTextLoad;
    sf::RectangleShape buttonSave;
    sf::Text buttonTextSave;
    sf::RectangleShape baseDebugConsole;
    sf::Text texDebugConsole;
    std::string consoleInput;
    bool isConsoleActive = false;
    sf::Clock debounceClock;
    float debounceDelay = 0.1f;
    float sectionLoadTilemapHeight;
    float sectionTileSizeHeight;
    sf::Text titleSection;
    sf::RectangleShape ButtonSectionOne;
    sf::RectangleShape ButtonSectionTwo;
    sf::RectangleShape ButtonSectionThree;
    sf::RectangleShape ButtonSectionFour;
    sf::RectangleShape ButtonSectionFive;
    sf::RectangleShape ButtonSectionSix;
    sf::Text titleBrushed;
    sf::RectangleShape ButtonTextureOne;
    sf::RectangleShape ButtonTextureTwo;
    sf::RectangleShape ButtonTextureThree;
    sf::RectangleShape ButtonTextureFour;
    sf::RectangleShape ButtonTextureFive;
    sf::RectangleShape ButtonTextureSix;
    sf::RectangleShape ButtonTextureSeven;
    sf::RectangleShape ButtonTextureEight;
    sf::RectangleShape ButtonTextureNine;
    sf::RectangleShape ButtonTextureTen;
    sf::RectangleShape ButtonTextureEleven;
    sf::RectangleShape ButtonTextureTwelve;
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