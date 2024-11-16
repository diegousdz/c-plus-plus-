#pragma once
#include "GameEntityManager.h"
#include "../Core/ResourceManager.h"
#include "../GameEntities/Player.h"
#include "../Tools/Tilemap.h"
#include <sstream>
#include <iostream>
#include <fstream>
class ResourceManager;

class Game
{
public:
    
    Game();
    float recalculateYPositionOfDoor(int row);
    void initializeTileTexturesLevelOne();

    void init(sf::RenderWindow& window, ResourceManager& resourceManager, Player& player);
    void checkForDoorsAndWinCondition(Player& player);
    void update(float deltaTime, Player& player);
    void draw(sf::RenderWindow& window, ResourceManager& resourceManager);
    void restartGame(Player& player, ResourceManager& resourceManager);

    GameEntityManager entityManager;
    bool  isGameMapLoaded = false;

    Tilemap tilemap;
    GameMap* gameMap = nullptr;
    MapSection** newMapSection = nullptr;
    int CurrentlySelectedIndex = -1;
    MapSection* currentSection;
    
    static const int NUM_LEVEL_TEXTURES = 10;
    sf::String texturesPathlevelOne[NUM_LEVEL_TEXTURES] = {
        "res/textures/World/32/tile_32_floor_B.png",
        "res/textures/World/32/tile_32_floor_b2.png",
        "res/textures/World/32/tile_32_floor_t.png",
        "res/textures/World/32/tile_32_floor_t2.png",
        "res/textures/World/32/tile_32_wall_l.png",
        "res/textures/World/32/tile_32_wall_l2.png",
        "res/textures/World/32/tile_32_wall_r.png",
        "res/textures/World/32/tile_32_wall_r2.png",
        "res/textures/World/32/tile_32_corner_l.png",
        "res/textures/World/32/tile_32_corner_r.png"
    };
    sf::Texture tileTexturesLevelOne[NUM_LEVEL_TEXTURES];
    
    GameMap* loadGameMap(const std::string& basePath, int playerLevel);

    std::vector<TileCell*> collisionCells;

private:
        
    float doorLevelOnePosX  = 0.0f;
    float doorLevelOnePosY  = 0.0f;
    float mapSectionNumberWhereDoorIsAtLevelOne = 6;

    float doorLevelTwoPosX = 0.0f;
    float doorLevelTwoPosY = 0.0f;
    float mapSectionNumberWhereDoorIsAtLevelTwo = 6;
    
    float doorLevelThreePosX = 0.0f;
    float doorLevelThreePosY = 0.0f;
    float mapSectionNumberWhereDoorIsAtLevelThree = 6;

    int winLevel = 1;
    int playerCurrentLevel = 1;
    
    sf::View camera;
    sf::Sprite backgroundLevelOne;
    bool loadMapSection(GameMap* gameMap, const std::string& basePath, int sectionIndex, sf::Texture* textures, int playerLevel);
};
