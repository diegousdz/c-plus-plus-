#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "./../GameEntities/Player.h"
#include "./../GameEntities/Orc.h"
#include "../Game/Game.h"

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
private:
    int playerTypeOfAnimationLastSet; 
    
    float deltaTime = 0.0f;
};