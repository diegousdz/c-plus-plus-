#pragma once
#include <SFML/Graphics.hpp>
#include "../GameEntities/Player.h"
#include "../Core/HelperFunctions.h"


struct TileCell;


class GameEntityManager
{
public:
    // Pointers to existing arrays of entities
    sf::RectangleShape* enemyEntities = nullptr;
    sf::RectangleShape* powerUpsEntities = nullptr;
    sf::RectangleShape* deadZoneEntities = nullptr;
    sf::RectangleShape* staticWorldEntities = nullptr;

    // Door entity (single instance)
    sf::RectangleShape doorEntity;

    // Flags indicating whether entities have been added
    bool hasEnemiesBeenAdded = false;
    bool hasPowerUpsBeenAdded = false;
    bool hasDeadZoneBeenAdded = false;
    bool hasDoorBeenAdded = false;
    bool hasStaticWorldBeenAdded = false;

    // Setter methods to assign pointers to existing arrays
    void setEnemyEntities(sf::RectangleShape* enemies)
    {
        enemyEntities = enemies;
        hasEnemiesBeenAdded = (enemies != nullptr);
    }

    sf::RectangleShape* getEnemyEntities()
    {
        return enemyEntities;
    }

    void setPowerUpsEntities(sf::RectangleShape* powerUps)
    {
        powerUpsEntities = powerUps;
        hasPowerUpsBeenAdded = (powerUps != nullptr);
    }

    sf::RectangleShape* getPowerUpsEntities()
    {
        return powerUpsEntities;
    }

    void setDeadZoneEntities(sf::RectangleShape* deadZones)
    {
        deadZoneEntities = deadZones;
        hasDeadZoneBeenAdded = (deadZones != nullptr);
    }

    sf::RectangleShape* getDeadZoneEntities()
    {
        return deadZoneEntities;
    }

    void setStaticWorldEntities(sf::RectangleShape* staticWorld)
    {
        staticWorldEntities = staticWorld;
        hasStaticWorldBeenAdded = (staticWorld != nullptr);
    }

    sf::RectangleShape* getStaticWorldEntities()
    {
        return staticWorldEntities;
    }

    // Door entity setter
    void setDoorEntity(const sf::RectangleShape& door)
    {
        doorEntity = door;
        hasDoorBeenAdded = true;
    }

    sf::RectangleShape& getDoorEntity()
    {
        return doorEntity;
    }

    // Collision detection methods
    int checkCollisionEnemies(Player& player);
    int checkCollisionPowerUps(Player& player);
    int checkCollisionDeadZone(Player& player);
    bool checkCollisionDoor(Player& player);
    int checkCollisionStaticWorld(Player& player);

    // Collision response methods
    void updatePlayerOnCollisionWithEnemy(Player& player, sf::RectangleShape& entity);
    void updatePlayerOnCollisionWithPowerUp(Player& player, sf::RectangleShape& entity);
    void updatePlayerOnCollisionWithDeadZone(Player& player, sf::RectangleShape& entity);
    void updatePlayerOnCollisionWithWorld(Player& player, TileCell* cell);
    void updatePlayerOnCollisionWithWorld(Player& player, sf::RectangleShape& entity);
    void updatePlayerOnCollisionWithDoor(Player& player);
    void createEnemiesLevelOne();

    // Initialization and update methods
    void gemInit(int levelEnemiesCount, sf::RectangleShape* enemies, int levelPowerUpsCount, sf::RectangleShape* powerUps, int levelDeadZoneCount, sf::RectangleShape* deadZones, int levelStaticWorldEntitiesCount, sf::RectangleShape* staticWorld, const sf::RectangleShape& door);
    void gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells);
    int checkCollisionWithCells(Player& player, const std::vector<TileCell*>& collisionCells);

    // Setters for entity counts
    void setEnemiesNumber(int value)
    {
        this->numberOfEnemies = value;
    }
    void setPowerUpsNumber(int value)
    {
        this->numberOfPowerUps = value;
    }
    void setDeadZoneNumber(int value)
    {
        this->numberDeadZone = value;
    }
    void setStaticWorldNumber(int value)
    {
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

private:
    int numberOfEnemies = 0;
    int numberOfPowerUps = 0;
    int numberDeadZone = 0;
    int numberOfStaticWorldEntities = 0;
};
