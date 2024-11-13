#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "./../GameEntities/Player.h"
#include "./../GameEntities/Orc.h"

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
    

    sf::RenderWindow gameWindow;
    sf::Clock clock;

    sf::Texture playerTexture;
    Player newGamePlayer;
    bool hasPlayerMoved = false;
    Orc orcWarriorsPoolShapes[5];
    void createEnemiesLevelOne();

    int getPlayerTypeOfAnimationLastSet() const;
    void setPlayerTypeOfAnimationLastSet(int type);

    sf::Texture playerIdleTexture;    
    sf::Texture playerRunTexture;     
    sf::Texture playerJumpTexture;

    bool isFirstFall = true;
    GUIHandler guiHandler;

    // ----------------------------------- GUI

    sf::Font font;
    sf::Text title;
    static constexpr int maxItemsMenu = 3;
    sf::Text menu[maxItemsMenu];

    // ----------------------------- top part
    sf::RectangleShape header;

    sf::Vector2<float> windowBounds = sf::Vector2<float>(0, 0);
    bool variablesDrawInitializedMainMenu = false;
    bool variablesDrawInitializedGame = false;
    bool isInGame;

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