#include "GameEntityManager.h"

#include "../Core/FileManager.h"
#include "../GameEntities/Orc.h"

struct TileCell;
#include "../Tools/Tilemap.h"
#include "../Core/ResourceManager.h"

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

void GameEntityManager::updatePlayerOnCollisionWithWorld(Player& player, TileCell* cell) {
    if (!cell) return;  // Safety check if cell is null
    const float GROUND_TOLERANCE = 0.0f;
    const float Y_OFFSET = 0.1f;  // Small offset to avoid overlap

    // Store the player's previous position for reset on collision
    sf::Vector2f previousPosition = player.getPosition();

    sf::FloatRect playerBounds = player.shape.getGlobalBounds();
    sf::FloatRect entityBounds = cell->shape.getGlobalBounds();

    // Calculate overlaps on each side
    float overlapLeft = (playerBounds.left + playerBounds.width) - entityBounds.left;
    float overlapRight = (entityBounds.left + entityBounds.width) - playerBounds.left;
    float overlapTop = (playerBounds.top + playerBounds.height) - entityBounds.top;
    float overlapBottom = (entityBounds.top + entityBounds.height) - playerBounds.top;

    // Find the smallest overlap
    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

    // Resolve collision based on the smallest overlap
    if (minOverlap == overlapTop) {
        // Collision from above
        player.setPosition({player.getPosition().x, entityBounds.top - playerBounds.height - GROUND_TOLERANCE});
        player.velocity.y = 0;
        player.isOnGround = true;
    } else if (minOverlap == overlapBottom) {
        // Collision from below
        player.setPosition({player.getPosition().x, entityBounds.top + entityBounds.height + Y_OFFSET});
        player.velocity.y = 0;
    } else if (minOverlap == overlapLeft) {
        // Collision from the left
        player.setPosition({entityBounds.left - playerBounds.width, player.getPosition().y});
        player.velocity.x = 0;
    } else if (minOverlap == overlapRight) {
        // Collision from the right
        player.setPosition({entityBounds.left + entityBounds.width, player.getPosition().y});
        player.velocity.x = 0;
    }

    // If collision still results in overlap, revert to the previous position (optional)
    // if (HelperFunctions::checkCollisionAABB(player.shape, cell->shape)) {
    //     player.setPosition(previousPosition);
    // }
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
        std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;\
        
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

void GameEntityManager::createEnemiesLevelOne()
{
    /* for (int i = 0; i < 5; i++)
     {
         Orc newOrc = resocreateOrc();
         orcWarriorsPoolShapes[i] = newOrc;
         float xPosition = 50.0f + (i * 70); 
         float yPosition = windowHeight - newOrc.enemySize;            
 
         orcWarriorsPoolShapes[i].shape.setPosition(xPosition, yPosition);
         
         // TODD:  gameWindow.draw(orcWarriorsPoolShapes[i].shape);
     } */
}

void GameEntityManager::calculateOrcAndPlayer(ResourceManager& resourceManager, Player& player)
{
    for (int i = 0; i < 5; i++)
    {
        Orc* orc = resourceManager.orcSpawnManagerOne[i];

        if (HelperFunctions::checkCollisionAABB(orc->shape, player.shape))
        {
            if (!orc->hasCollidedWithPlayer)
            {
                std::cout << "Player LIFE " << player.life << std::endl;
                player.takeDamage(1);
                std::cout << "Player LIFE " << player.life << std::endl;
             //   player.life -= 1; // Reduce player's life by 1
                orc->hasCollidedWithPlayer = true;

                // Optional: Apply knockback to player
                float knockbackStrength = 200.0f;
                player.velocity.x = (player.shape.getPosition().x < orc->shape.getPosition().x) ? -knockbackStrength : knockbackStrength;
                std::cout << "Player hit by orc! Remaining life: " << player.life << std::endl;
            }
        }
        else
        {
            orc->hasCollidedWithPlayer = false;
        }
    }
}
void GameEntityManager::calculateOrcAndWorld(ResourceManager& resourceManager, const std::vector<TileCell*>& collisionCells)
{
    const float GROUND_TOLERANCE = 0.0f;

    for (int i = 0; i < 5; i++)
    {
        Orc* orc = resourceManager.orcSpawnManagerOne[i];

        for (TileCell* cell : collisionCells)
        {
            if (HelperFunctions::checkCollisionAABB(orc->shape, cell->shape))
            {
                sf::FloatRect orcBounds = orc->shape.getGlobalBounds();
                sf::FloatRect cellBounds = cell->shape.getGlobalBounds();

                // Calculate overlap distances
                float overlapLeft = (orcBounds.left + orcBounds.width) - cellBounds.left;
                float overlapRight = (cellBounds.left + cellBounds.width) - orcBounds.left;
                float overlapTop = (orcBounds.top + orcBounds.height) - cellBounds.top;
                float overlapBottom = (cellBounds.top + cellBounds.height) - orcBounds.top;

                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                if (minOverlap == overlapTop)
                {
                    // Collision from above
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBounds.top - orcBounds.height - GROUND_TOLERANCE);
                    orc->velocity.y = 0;
                    orc->isOnGround = true;
                }
                else if (minOverlap == overlapBottom)
                {
                    // Collision from below
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBounds.top + cellBounds.height + GROUND_TOLERANCE);
                    orc->velocity.y = 0;
                }
                else if (minOverlap == overlapLeft)
                {
                    // Collision from the left
                    orc->shape.setPosition(cellBounds.left - orcBounds.width, orc->shape.getPosition().y);
                    orc->velocity.x = -abs(orc->velocity.x); // Reverse direction
                }
                else if (minOverlap == overlapRight)
                {
                    // Collision from the right
                    orc->shape.setPosition(cellBounds.left + cellBounds.width, orc->shape.getPosition().y);
                    orc->velocity.x = abs(orc->velocity.x); // Reverse direction
                }
            }
        }
    }
}




void GameEntityManager::gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells)
{
    if (hasEnemiesBeenAdded) {
        if (!hasEnemyIndex) {
            enemyIndex = checkCollisionEnemies(player);
            hasEnemyIndex = true;
        }
        if (enemyIndex != -1) {
            updatePlayerOnCollisionWithEnemy(player, enemyEntities[enemyIndex]);
        }
    }

    if (hasPowerUpsBeenAdded) {
        if (!hasPowerUpIndex) {
            powerUpIndex = checkCollisionPowerUps(player);
            hasPowerUpIndex = true;
        }

        if (powerUpIndex != -1) {
            updatePlayerOnCollisionWithPowerUp(player, powerUpsEntities[powerUpIndex]);
        }
    }

    if (hasDoorBeenAdded) {
        if (checkCollisionDoor(player)) {
            updatePlayerOnCollisionWithDoor(player);
        }
    }

    if (hasDeadZoneBeenAdded) {
        if (!hasDeadZoneIndex) {
            deadZoneIndex = checkCollisionDeadZone(player);
            hasDeadZoneIndex = true;
        }

        if (deadZoneIndex != -1) {
            updatePlayerOnCollisionWithDeadZone(player, deadZoneEntities[deadZoneIndex]);
        }
    }

    if (hasStaticWorldBeenAdded) {
        if (!hasStaticWorldIndex) {
            staticWorldIndex = checkCollisionStaticWorld(player);
            hasStaticWorldIndex = true;
        }

        if (staticWorldIndex != -1) {
            //  updatePlayerOnCollisionWithWorld(player, staticWorldEntities[staticWorldIndex]);
        }
    }
    
    // Check and resolve collisions with cells in collisionCells
    for (TileCell* cell : collisionCells) {
        if (HelperFunctions::checkCollisionAABB(player.shape, cell->shape)) {
            // Check and resolve each collision based on direction
            sf::FloatRect playerBounds = player.shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->shape.getGlobalBounds();

            // Calculate overlap distances
            float overlapLeft = (playerBounds.left + playerBounds.width) - cellBounds.left;
            float overlapRight = (cellBounds.left + cellBounds.width) - playerBounds.left;
            float overlapTop = (playerBounds.top + playerBounds.height + 2) - cellBounds.top;
            float overlapBottom = (cellBounds.top + cellBounds.height + 2) - playerBounds.top;

            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapTop) {
                // Collision from above
                player.setPosition({player.getPosition().x, cellBounds.top - playerBounds.height});
                player.velocity.y = 0;
                player.isOnGround = true;  // Set grounded if collision occurs from abovep
                player.isJumping = false;
                
            } else if (minOverlap == overlapBottom) {
                // Collision from below
                player.setPosition({player.getPosition().x, cellBounds.top + cellBounds.height});
                player.velocity.y = 0;
            } else if (minOverlap == overlapLeft) {
                // Collision from the left
                player.setPosition({cellBounds.left - playerBounds.width, player.getPosition().y});
                player.velocity.x = 0;
            } else if (minOverlap == overlapRight) {
                // Collision from the right
                player.setPosition({cellBounds.left + cellBounds.width, player.getPosition().y});
                player.velocity.x = 0;
            }
        }
    }
}



int GameEntityManager::checkCollisionWithCells(Player& player, const std::vector<TileCell*>& collisionCells) {
    for (size_t i = 0; i < collisionCells.size(); ++i) {
        if (HelperFunctions::checkCollisionAABB(player.shape, collisionCells[i]->shape)) {
            return i;  // Return the index of the cell in collision
        }
    }
    return -1;  // No collision found
}