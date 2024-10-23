#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include "./../GameEntities/Player.h"
#include "./../GameEntities/Orc.h"

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

    Player newGamePlayer;
    Orc orcWarriorsPoolShapes[5];
    void createEnemiesLevelOne();
    
private:
    float deltaTime = 0.0f;
};