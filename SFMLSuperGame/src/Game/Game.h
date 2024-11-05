#pragma once
#include "../GameEntities/Player.h"

struct gameSection
{
    sf::String id = "map#1";

    int numberOfSections  = 2;
    
    int width;
    int height;
    
    float positionX;
    float positionY;
};

class Game
{
public:
    
    Game();  // Constructor with parameters

    void init(sf::RenderWindow& window, Player user);
    void updateBackgroundPosition();
    void update(float deltaTime, Player player);
    void draw(sf::RenderWindow& window, Player user);
    
    void NewGame();
    void LoadGame();
    void createEnemiesLevelOne();

    void setMapWidth(int totalMapSectionWidth);

private:
    int mapWidth = 0;
    sf::View camera;
    sf::Sprite background;
    sf::Vector2f worldOffset;
};
