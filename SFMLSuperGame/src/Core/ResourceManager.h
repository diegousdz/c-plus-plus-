#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "./../GameEntities/Player.h"
#include "./../GameEntities/Orc.h"
#include "FileManager.h"
#include "GUIHandler.h"

class ResourceManager
{
public:
    // Engine
    int windowWidth = 512;
    int windowHeight  = 512;
    
    void setWindowWidth(int width) { windowWidth = width; }
    void setWindowHeight(int height) { windowHeight = height; }

    void loadResources();
    void loadGameBackgrounds();
    void setDeltaTime();
    float getDeltaTime() const;
    
    // Game variables
    bool isMainMenuActive = true;
    bool isGameInitialized = false;
    int currentOptionSelected = 0;
    
    FileManager fileManager;
    sf::RenderWindow gameWindow;
    sf::Clock clock;

    sf::Texture playerTexture;
    Player newGamePlayer;
    bool hasPlayerMoved = false;
    static constexpr  int NUMBER_OF_ENEMY_LEVEL_ONE = 10;
    Orc* orcWarriorsPoolShapes[NUMBER_OF_ENEMY_LEVEL_ONE];
    void createEnemiesLevelOne(float initialPositionX, float initialPositionY);

    int getPlayerTypeOfAnimationLastSet() const;
    void setPlayerTypeOfAnimationLastSet(int type);

    sf::Texture playerIdleTexture;    
    sf::Texture playerRunTexture;     
    sf::Texture playerJumpTexture;
    sf::Texture playerAttack;

    bool isFirstFall = true;
    GUIHandler guiHandler;

    // ----------------------------------- GUI

    bool savedGameAvailable;
    sf::Font font;
    sf::Text title;
    static constexpr int maxItemsMenu = 3;
    sf::Text menu[maxItemsMenu];
    sf::View uiView;
    
    sf::Vector2<float> windowBounds = sf::Vector2<float>(0, 0);

    // ----------------------------- top part
    sf::RectangleShape header;

    sf::RectangleShape healthBarBorder;
    sf::RectangleShape healthBarFill;
    
    sf::RectangleShape energyBar;
    
    bool variablesDrawInitializedMainMenu = false;
    bool variablesDrawInitializedGame = false;
    bool isInGame;
    
    sf::Text lifeText, healthText, energyText;
    std::vector<sf::Sprite> hearts;
    sf::Texture heartTexture;

    std::vector<sf::RectangleShape> inventorySlots;
    std::vector<sf::Sprite> inventoryIcons;
    std::vector<sf::Text> inventoryCounts;
    std::vector<sf::Texture> itemTextures;
    

    // -------------------------------- bottom part

    sf::RectangleShape footer;

    // ----------------------------- Game class

    sf::Texture backgroundOne;
    sf::Texture backgroundTwo;
    sf::Texture backgroundThree;

    sf::Sprite  backgroundSpriteOne;
    sf::Sprite  backgroundSpriteTwo;
    sf::Sprite  backgroundSpriteThree;
    sf::Sprite& getBackgroundSpriteOne() { return backgroundSpriteOne; }

    bool hasTextureToSpriteOneFinished = false;
    bool hasTextureToSpriteTwoFinished = false;
    bool hasTextureToSpriteThreeFinished = false;

    bool hasTexturesForGameLoaded = false;

    sf::Vector2f initalSpawnPositionLevelOne = sf::Vector2f(50, 0);
    sf::Vector2f initalSpawnPositionLevelTwo;
    sf::Vector2f initalSpawnPositionLevelThree;

    int currentUserLevel = 1;
    float deadZoneYPosition = 510.0f;
    bool gameOver = false; // Add this variable to track game over state
    bool gameOverInitialized = false;
    sf::Text gameOverText;
    sf::Text restartPrompt;
    
private:
    int playerTypeOfAnimationLastSet; 
    
    float deltaTime = 0.0f;
};