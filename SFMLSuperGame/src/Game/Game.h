#pragma once
#include "GameEntityManager.h"
#include "../Core/ResourceManager.h"
#include "../GameEntities/Player.h"

class ResourceManager;

class Game
{
public:
    
    Game();  

    void init(sf::RenderWindow& window, ResourceManager& resourceManager, Player& player);
    void inputHandle();
    void update(float deltaTime, Player& player);
    void draw(sf::RenderWindow& window, ResourceManager& resourceManager);
    
    GameEntityManager entityManager;
    bool  isGameMapLoaded = false;
    
    void composeRender(sf::RenderWindow& window, ResourceManager& resourceManager);
    
private:
    sf::View camera;
    sf::Sprite backgroundLevelOne;
};
