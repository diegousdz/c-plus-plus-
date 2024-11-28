#pragma once
#include "GameEntityManager.h"
#include "../Core/ResourceManager.h"
#include "../GameEntities/Player.h"
#include "../Tools/Tilemap.h"

#include <sstream>
#include <iostream>
#include <fstream>

class ResourceManager;

class Game {
public:
    Game();
    float recalculateYPosition(int row);
    void initializeTileTexturesLevelOne();

    void init(sf::RenderWindow& window, ResourceManager& resourceManager, Player& player);
    void checkForDoorsAndWinCondition(Player& player, ResourceManager& resourceManager);
    void update(float deltaTime, Player& player, ResourceManager& resourceManager);
    void draw(sf::RenderWindow& window, ResourceManager& resourceManager);
    void restartGame(Player& player, ResourceManager& resourceManager);

    GameEntityManager entityManager;
    bool isGameMapLoaded = false;

    Tilemap tilemap;
    GameMap* gameMap = nullptr;
    MapSection** newMapSection = nullptr;
    int CurrentlySelectedIndex = -1;
    MapSection* currentSection;

    static const int NUM_LEVEL_TEXTURES = 18;

    sf::String texturesPathlevelOne[NUM_LEVEL_TEXTURES] = {
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

    sf::Texture tileTexturesLevelOne[NUM_LEVEL_TEXTURES];
    GameMap* loadGameMap(const std::string& basePath, int playerLevel);

    std::vector<TileCell*> collisionCells;

private:
    float doorLevelOnePosX = 0.0f;
    float doorLevelOnePosY = 0.0f;
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