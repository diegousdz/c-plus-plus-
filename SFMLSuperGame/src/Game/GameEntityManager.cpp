#include "GameEntityManager.h"

#include "../Core/FileManager.h"


void GameEntityManager::gemInit(int levelEnemiesCount, sf::RectangleShape* enemies,
                 int levelPowerUpsCount, sf::RectangleShape* powerUps,
                 int levelDeadZoneCount, sf::RectangleShape* deadZones,
                 int levelStaticWorldEntitiesCount, sf::RectangleShape* staticWorld,
                 const sf::RectangleShape& door)
{
    // define the max lenght of the entities array
    setEnemiesNumber(levelEnemiesCount);
    setPowerUpsNumber(levelPowerUpsCount);
    setDeadZoneNumber(levelDeadZoneCount);
    setStaticWorldNumber(levelStaticWorldEntitiesCount);
    
    setEnemyEntities(enemies);
    setPowerUpsEntities(powerUps);
    setDeadZoneEntities(deadZones);
    setStaticWorldEntities(staticWorld);
    setDoorEntity(door);
}

int GameEntityManager::checkCollisionEnemies(Player& player)
{
    for (int i = 0; i < this->numberOfEnemies; ++i)
    {
        if (HelperFunctions::checkCollisionAABB(player.shape, enemyEntities[i]))
        {
            return i;
        }
    }
    return -1; 
}

int GameEntityManager::checkCollisionPowerUps(Player& player)
{
    for (int i = 0; i < this->numberOfPowerUps; ++i)
    {
        if (HelperFunctions::checkCollisionAABB(player.shape, powerUpsEntities[i]))
        {
            return i;
        }
    }
    return -1; 
}

int GameEntityManager::checkCollisionDeadZone(Player& player)
{
    for (int i = 0; i < this->numberDeadZone; ++i)
    {
        if (HelperFunctions::checkCollisionAABB(player.shape, deadZoneEntities[i]))
        {
            return i; 
        }
    }
    return -1; 
}

bool GameEntityManager::checkCollisionDoor(Player& player)
{
    return HelperFunctions::checkCollisionAABB(player.shape, doorEntity);
}

int GameEntityManager::checkCollisionStaticWorld(Player& player)
{
    for (int i = 0; i < this->numberOfStaticWorldEntities; ++i)
    {
        if (HelperFunctions::checkCollisionAABB(player.shape, staticWorldEntities[i]))
        {
            return i; 
        }
    }
    return -1; 
}

// Implement the collision response methods as needed
void GameEntityManager::updatePlayerOnCollisionWithEnemy(Player& player, sf::RectangleShape& entity)
{
    // Implement the logic for when the player collides with an enemy
}

void GameEntityManager::updatePlayerOnCollisionWithPowerUp(Player& player, sf::RectangleShape& entity)
{
    // Implement the logic for when the player collides with a power-up
}

void GameEntityManager::updatePlayerOnCollisionWithDeadZone(Player& player, sf::RectangleShape& entity)
{
    // Implement the logic for when the player collides with a dead zone
}

void GameEntityManager::updatePlayerOnCollisionWithWorld(Player& player, sf::RectangleShape& entity)
{
    sf::FloatRect playerBounds = player.shape.getGlobalBounds();
    sf::FloatRect entityBounds = entity.getGlobalBounds();
    
    // Calculate overlap
    float overlapLeft = (playerBounds.left + playerBounds.width) - entityBounds.left;
    float overlapRight = (entityBounds.left + entityBounds.width) - playerBounds.left;
    float overlapTop = (playerBounds.top + playerBounds.height) - entityBounds.top;
    float overlapBottom = (entityBounds.top + entityBounds.height) - playerBounds.top;

    // Find the smallest overlap
    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

    // Resolve collision based on the smallest overlap
    if (minOverlap == overlapLeft) {
        // Collision from the left
        player.setPosition({entityBounds.left - playerBounds.width, player.getPosition().y});
        player.velocity.x = 0;
    }
    else if (minOverlap == overlapRight) {
        // Collision from the right
        player.setPosition({entityBounds.left + entityBounds.width, player.getPosition().y});
        player.velocity.x = 0;
    }
    else if (minOverlap == overlapTop) {
        // Collision from above
        player.setPosition({player.getPosition().x, entityBounds.top - playerBounds.height});
        player.velocity.y = 0;
        player.isOnGround = true;
    }
    else if (minOverlap == overlapBottom) {
        // Collision from below
        player.setPosition({player.getPosition().x, entityBounds.top + entityBounds.height});
        player.velocity.y = 0;
    }
}

void GameEntityManager::updatePlayerOnCollisionWithDoor(Player& player)
{
    // Implement the logic for when the player collides with the door
}


void GameEntityManager::gemUpdate(Player& player)
{
    if (hasEnemiesBeenAdded)
    {
        if(!hasEnemyIndex)
        {
            enemyIndex = checkCollisionEnemies(player);
            hasEnemyIndex = true;
        }
        if (enemyIndex != -1)
        {
            updatePlayerOnCollisionWithEnemy(player, enemyEntities[enemyIndex]);
        }
    }

    if (hasPowerUpsBeenAdded)
    {
        if(!hasPowerUpIndex)
        {
            powerUpIndex = checkCollisionPowerUps(player);
            hasPowerUpIndex = true;
        }
        
        if (powerUpIndex != -1)
        {
            updatePlayerOnCollisionWithPowerUp(player, powerUpsEntities[powerUpIndex]);
        }
    }

    if (hasDoorBeenAdded)
    {
        if (checkCollisionDoor(player))
        {
            updatePlayerOnCollisionWithDoor(player);
        }
    }

    if (hasDeadZoneBeenAdded)
    {
        if(!hasDeadZoneIndex)
        {
            deadZoneIndex = checkCollisionDeadZone(player);
            hasDeadZoneIndex = true;
        }
       
        if (checkCollisionDeadZone(player) != -1)
        {
            updatePlayerOnCollisionWithDeadZone(player, deadZoneEntities[deadZoneIndex]);
        }
    }

    if (hasStaticWorldBeenAdded)
    {
        if(hasStaticWorldIndex)
        {
            staticWorldIndex = checkCollisionStaticWorld(player);
            hasStaticWorldIndex = true;
        }
        
        if (staticWorldIndex != -1)
        {
            updatePlayerOnCollisionWithWorld(player, staticWorldEntities[staticWorldIndex]);
        }
    }
}
