#pragma once
#include <SFML/Graphics.hpp>
#include "../GameEntities/Player.h"
#include "../Core/HelperFunctions.h"

class Orc;
struct TileCell;

class ResourceManager;

class GameEntityManager
{
public:
    sf::RectangleShape* enemyEntities = nullptr;
    sf::RectangleShape* powerUpsEntities = nullptr;
    sf::RectangleShape* deadZoneEntities = nullptr;
    sf::RectangleShape* staticWorldEntities = nullptr;
    sf::RectangleShape doorEntity;

    bool hasEnemiesBeenAdded = false;
    bool hasPowerUpsBeenAdded = false;
    bool hasDeadZoneBeenAdded = false;
    bool hasDoorBeenAdded = false;
    bool hasStaticWorldBeenAdded = false;

    void setEnemyEntities(sf::RectangleShape* enemies) {
        enemyEntities = enemies;
        hasEnemiesBeenAdded = (enemies != nullptr);
    }

    sf::RectangleShape* getEnemyEntities() {
        return enemyEntities;
    }

    void setPowerUpsEntities(sf::RectangleShape* powerUps) {
        powerUpsEntities = powerUps;
        hasPowerUpsBeenAdded = (powerUps != nullptr);
    }

    sf::RectangleShape* getPowerUpsEntities() {
        return powerUpsEntities;
    }

    void setDeadZoneEntities(sf::RectangleShape* deadZones) {
        deadZoneEntities = deadZones;
        hasDeadZoneBeenAdded = (deadZones != nullptr);
    }

    sf::RectangleShape* getDeadZoneEntities() {
        return deadZoneEntities;
    }

    void setStaticWorldEntities(sf::RectangleShape* staticWorld) {
        staticWorldEntities = staticWorld;
        hasStaticWorldBeenAdded = (staticWorld != nullptr);
    }

    sf::RectangleShape* getStaticWorldEntities() {
        return staticWorldEntities;
    }

    void setDoorEntity(const sf::RectangleShape& door) {
        doorEntity = door;
        hasDoorBeenAdded = true;
    }

    sf::RectangleShape& getDoorEntity() {
        return doorEntity;
    }
    
    void calculateOrcAndPlayer(ResourceManager& resourceManager, Player& player);
    void calculateOrcAndWorld( ResourceManager& resourceManager, const std::vector<TileCell*>& collisionCells);
    
    void gemInit(int levelEnemiesCount, sf::RectangleShape* enemies, int levelPowerUpsCount, sf::RectangleShape* powerUps, int levelDeadZoneCount, sf::RectangleShape* deadZones, int levelStaticWorldEntitiesCount, sf::RectangleShape* staticWorld, const sf::RectangleShape& door);
    void gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells, ResourceManager& resourceManager);
    
    void setEnemiesNumber(int value) {
        this->numberOfEnemies = value;
    }
    
    void setPowerUpsNumber(int value) {
        this->numberOfPowerUps = value;
    }

    void setDeadZoneNumber(int value) {
        this->numberDeadZone = value;
    }
    
    void setStaticWorldNumber(int value) {
        this->numberOfStaticWorldEntities = value;
    }
    
    int enemyIndex = -1;
    bool hasEnemyIndex = false;
    int powerUpIndex = -1;
    bool hasPowerUpIndex = false;
    int deadZoneIndex = -1;
    bool hasDeadZoneIndex = false;
    int staticWorldIndex = -1;
    bool hasStaticWorldIndex = false;
    float GROUND_TOLERANCE = 1.0f;

    sf::FloatRect playerBounds;
    sf::FloatRect cellBounds;

    float overlapLeft;
    float overlapRight;
    float overlapTop;
    float overlapBottom;

    float minOverlap;

    float overlapLeftPlayerOrc;
    float overlapRightPlayerOrc;
    float overlapTopPlayerOrc;
    float overlapBottomPlayerOrc;
    float minOverlapPlayerOrc;

    sf::FloatRect orcBoundsOrc;
    sf::FloatRect cellBoundsOrc;

    float overlapLeftOrc;
    float overlapRightOrc;
    float overlapTopOrc;
    float overlapBottomOrc;
    float minOverlapOrc;

    Orc* orc;
private:
    int numberOfEnemies = 0;
    int numberOfPowerUps = 0;
    int numberDeadZone = 0;
    int numberOfStaticWorldEntities = 0;
};