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
        orc = resourceManager.orcSpawnManagerOne[i];
        if (HelperFunctions::checkCollisionAABB(orc->shape, player.shape)) {
            sf::FloatRect orcBounds = orc->shape.getGlobalBounds();
            sf::FloatRect playerBounds = player.shape.getGlobalBounds();

            overlapLeftPlayerOrc = (playerBounds.left + playerBounds.width) - orcBounds.left;
            overlapRightPlayerOrc = (orcBounds.left + orcBounds.width) - playerBounds.left;
            overlapTopPlayerOrc = (playerBounds.top + playerBounds.height) - orcBounds.top;
            overlapBottomPlayerOrc = (orcBounds.top + orcBounds.height) - playerBounds.top;

            minOverlapPlayerOrc = std::min({overlapLeftPlayerOrc, overlapRightPlayerOrc, overlapTopPlayerOrc, overlapBottomPlayerOrc});

            if (!orc->hasCollidedWithPlayer) {
                if (minOverlapPlayerOrc == overlapTopPlayerOrc) {
                    player.takeDamage(1);
                    orc->hasCollidedWithPlayer = true;
                    player.velocity.y = -100.0f;
                } else if (minOverlapPlayerOrc == overlapLeftPlayerOrc || minOverlapPlayerOrc == overlapRightPlayerOrc) {
                    player.takeDamage(1);
                    orc->hasCollidedWithPlayer = true;
                    float knockbackStrength = 100.0f;
                    player.velocity.x = (playerBounds.left < orcBounds.left) ? -knockbackStrength : knockbackStrength;
                }
            }
        } else {
            orc->hasCollidedWithPlayer = false;
        }
    }
}


void GameEntityManager::calculateOrcAndWorld(ResourceManager& resourceManager, const std::vector<TileCell*>& collisionCells) {

    for (int i = 0; i < 5; ++i) {
        orc = resourceManager.orcSpawnManagerOne[i];
        for (TileCell* cell : collisionCells) {
            if (HelperFunctions::checkCollisionAABB(orc->shape, cell->shape)) {
                orcBoundsOrc = orc->shape.getGlobalBounds();
                cellBoundsOrc = cell->shape.getGlobalBounds();

                overlapLeftOrc = (orcBoundsOrc.left + orcBoundsOrc.width) - cellBoundsOrc.left;
                overlapRightOrc = (cellBoundsOrc.left + cellBoundsOrc.width) - orcBoundsOrc.left;
                overlapTopOrc = (orcBoundsOrc.top + orcBoundsOrc.height) - cellBoundsOrc.top;
                overlapBottomOrc = (cellBoundsOrc.top + cellBoundsOrc.height) - orcBoundsOrc.top;

                minOverlapOrc = std::min({overlapLeftOrc, overlapRightOrc, overlapTopOrc, overlapBottomOrc});
                
                if (minOverlapOrc == overlapTopOrc) {
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBoundsOrc.top - orcBoundsOrc.height);
                    orc->isOnGround = true;
                } else if (minOverlapOrc == overlapBottomOrc) {
                    orc->shape.setPosition(orc->shape.getPosition().x, cellBoundsOrc.top + cellBoundsOrc.height);
                    orc->velocity.y = 0;
                } else if (minOverlapOrc == overlapLeftOrc) {
                    orc->shape.setPosition(cellBoundsOrc.left - orcBoundsOrc.width, orc->shape.getPosition().y);
                    orc->velocity.x = -std::abs(orc->velocity.x);
                } else if (minOverlapOrc == overlapRightOrc) {
                    orc->shape.setPosition(cellBoundsOrc.left + cellBoundsOrc.width, orc->shape.getPosition().y);
                    orc->velocity.x = std::abs(orc->velocity.x);
                }
            }
        }
    }
}

void GameEntityManager::gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells, ResourceManager& resourceManager) {
    player.updateGroundState();
    
    for (TileCell* cell : collisionCells) {
        if (HelperFunctions::checkCollisionAABB(player.shape, cell->shape)) {
            playerBounds = player.shape.getGlobalBounds();
            cellBounds = cell->shape.getGlobalBounds();

            overlapLeft = (playerBounds.left + playerBounds.width) - cellBounds.left;
            overlapRight = (cellBounds.left + cellBounds.width) - playerBounds.left;
            overlapTop = (playerBounds.top + playerBounds.height) - cellBounds.top;
            overlapBottom = (cellBounds.top + cellBounds.height) - playerBounds.top;

            minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

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
            
            if (player.velocity.x == 0 && !resourceManager.gameOver && !resourceManager.gameWin) {
                resourceManager.soundSequencer.playPlayerIdleSound();
            }
          
        }
    }
}