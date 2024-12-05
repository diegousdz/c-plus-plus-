#include "GameEntityManager.h"
#include "../Core/FileManager.h"
#include "../GameEntities/Orc.h"
#include "../Tools/Tilemap.h"
#include "../Core/ResourceManager.h"

void GameEntityManager::gemInit(int levelEnemiesCount, sf::RectangleShape* enemies, int levelPowerUpsCount, sf::RectangleShape* powerUps, int levelDeadZoneCount, sf::RectangleShape* deadZones, int levelStaticWorldEntitiesCount, sf::RectangleShape* staticWorld, const sf::RectangleShape& door) {
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

void GameEntityManager::calculateOrcAndPlayer(ResourceManager& resourceManager, Player& player) {
    for (int i = 0; i < 5; ++i) {
        Orc* orc = resourceManager.orcSpawnManagerOne[i];
        if (HelperFunctions::checkCollisionAABB(orc->shape, player.shape)) {
            if (!orc->hasCollidedWithPlayer) {
                player.takeDamage(1);
                orc->hasCollidedWithPlayer = true;

                float knockbackStrength = 200.0f;
                player.velocity.x = (player.shape.getPosition().x < orc->shape.getPosition().x) ? -knockbackStrength : knockbackStrength;
            }
        } else {
            orc->hasCollidedWithPlayer = false;
        }
    }
}

void GameEntityManager::calculateOrcAndWorld(ResourceManager& resourceManager, const std::vector<TileCell*>& collisionCells) {
    const float GROUND_TOLERANCE = 0.0f;

    for (int i = 0; i < 5; ++i) {
        Orc* orc = resourceManager.orcSpawnManagerOne[i];
        for (TileCell* cell : collisionCells) {
            if (HelperFunctions::checkCollisionAABB(orc->shape, cell->shape)) {
                sf::FloatRect orcBounds = orc->shape.getGlobalBounds();
                sf::FloatRect cellBounds = cell->shape.getGlobalBounds();

                float overlapLeft = (orcBounds.left + orcBounds.width) - cellBounds.left;
                float overlapRight = (cellBounds.left + cellBounds.width) - orcBounds.left;
                float overlapTop = (orcBounds.top + orcBounds.height) - cellBounds.top;
                float overlapBottom = (cellBounds.top + cellBounds.height) - orcBounds.top;

                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
                
                if (minOverlap == overlapTop) {
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBounds.top - orcBounds.height - GROUND_TOLERANCE);
                    orc->velocity.y = 0;
                    orc->isOnGround = true;
                } else if (minOverlap == overlapBottom) {
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBounds.top + cellBounds.height + GROUND_TOLERANCE);
                    orc->velocity.y = 0;
                } else if (minOverlap == overlapLeft) {
                    orc->shape.setPosition(cellBounds.left - orcBounds.width, orc->shape.getPosition().y);
                    orc->velocity.x = -std::abs(orc->velocity.x);
                } else if (minOverlap == overlapRight) {
                    orc->shape.setPosition(cellBounds.left + cellBounds.width, orc->shape.getPosition().y);
                    orc->velocity.x = std::abs(orc->velocity.x);
                }
            }
        }
    }
}

void GameEntityManager::gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells) {
    for (TileCell* cell : collisionCells) {
        if (HelperFunctions::checkCollisionAABB(player.shape, cell->shape)) {
            sf::FloatRect playerBounds = player.shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->shape.getGlobalBounds();

            float overlapLeft = (playerBounds.left + playerBounds.width) - cellBounds.left;
            float overlapRight = (cellBounds.left + cellBounds.width) - playerBounds.left;
            float overlapTop = (playerBounds.top + playerBounds.height) - cellBounds.top;
            float overlapBottom = (cellBounds.top + cellBounds.height) - playerBounds.top;

            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapTop) {
                player.setPosition({player.getPosition().x, cellBounds.top - playerBounds.height});
                player.velocity.y = 0;
                player.isOnGround = true;
                player.isJumping = false;
            } else if (minOverlap == overlapBottom) {
                player.setPosition({player.getPosition().x, cellBounds.top + cellBounds.height});
                player.velocity.y = 0;
            } else if (minOverlap == overlapLeft) {
                player.setPosition({cellBounds.left - playerBounds.width, player.getPosition().y});
                player.velocity.x = 0;
            } else if (minOverlap == overlapRight) {
                player.setPosition({cellBounds.left + cellBounds.width, player.getPosition().y});
                player.velocity.x = 0;
            }
        }
    }
}