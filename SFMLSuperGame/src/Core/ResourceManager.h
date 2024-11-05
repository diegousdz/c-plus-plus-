#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "./../GameEntities/Player.h"
#include "./../GameEntities/Orc.h"
#include "../Game/Game.h"
#include "GUIHandler.h"


class ResourceManager
{
public:
    // Engine
    const int windowWidth = 512;
    const int windowHeight  = 512;

    void loadResources();
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
    Orc orcWarriorsPoolShapes[5];
    void createEnemiesLevelOne();

    int getPlayerTypeOfAnimationLastSet() const;
    void setPlayerTypeOfAnimationLastSet(int type);

    sf::Texture playerIdleTexture;    
    sf::Texture playerRunTexture;     
    sf::Texture playerJumpTexture;
    
    Game game;
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

private:
    int playerTypeOfAnimationLastSet; 
    
    float deltaTime = 0.0f;
};