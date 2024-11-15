#include "GameEntityManager.h"

#include "../Core/FileManager.h"

struct TileCell;
#include "../Tools/Tilemap.h"

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
    const float GROUND_TOLERANCE = 1.0f;
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

void GameEntityManager::gemUpdate(Player& player, const std::vector<TileCell*>& collisionCells) {

    
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

    // Check collisions with cells stored in collisionCells
    int cellIndex = checkCollisionWithCells(player, collisionCells);
    if (cellIndex != -1) {
        // You could implement logic here for handling the collision, such as updating the player position
        // For example:
        
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
            float overlapTop = (playerBounds.top + playerBounds.height) - cellBounds.top;
            float overlapBottom = (cellBounds.top + cellBounds.height) - playerBounds.top;

            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapTop) {
                // Collision from above
                player.setPosition({player.getPosition().x, cellBounds.top - playerBounds.height - GROUND_TOLERANCE});
                player.velocity.y = 0;
                player.isOnGround = true;  // Set grounded if collision occurs from above
            } else if (minOverlap == overlapBottom) {
                // Collision from below
                player.setPosition({player.getPosition().x, cellBounds.top + cellBounds.height + GROUND_TOLERANCE});
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

//


// If collision between player and eniemies enter en battle function mode

// enemies are spawn at a wave system not all together. they should be allocated in a pool represented in an arrays
// from there I want to spawn a new one with a max of spawn of (define max enemiesPerWave).

// so the idea is that I have the ability to enter in battle mode?

/// maybe the most efficient way isnt this one..
///
/// but maybe there could be a battle where there is multiple Orcs and only 1 player.
///
/// Like if collision with 1 orc. enter player parameter and inside the function I check if player exist, if exist.
///
/// then do create an array static of 2 arrays of fixed 5 orcs.
///
/// that I once they "Die". they tooggle of visibility, modify player parameters of health and reposition the orc to the initial spawn point positon 1.
///
/// I will have 2 spawn point position per map section.
///
/// the spawn point should be represented as Rectangle shape with color red
///
/// This way I can visually position the spawn points. To do so, also modify temporarey the update function to show the X and Y position of player.
///
/// in resource manager save this coordinates so are accesible to the game class
///
/// in the game class manage the life cycle of create at init the orcs to allocate them.
///
/// I need to create the function of createSpawnPoing that groups the process of making one instance of a spawnpoint that will contain the previosly allocated
///
/// init after allocation the spawnpoints so they start to spawn. 2 at the time once the player enter Xposition. this will trigger the spawn of the first 2 warrior orcs
///
/// last not least each orc should mirror direction. ( think this is done my negating the valio of the velocity.)
///
/// when is not a collider type ground, like the collision is from the bottom. if is left, mirror the position of the Orc, the idea is to mimic how super mario bros enemies work
///
/// Each enemy / orc should manage a life cycle. Of run / attack / die / idle.
///
/// create a state machine to handle this as enum.
///
/// ORcs should have this rectangle that is 100 pixels wide and is position is calculated to be in the middle of the shape. so copy position but apply the offset so its not in center. so its facing the direction of the orc.
///
/// for example the player when switchs facing direction the sprite is changed by a hack I found, this is very delicate.
///
/// so the idea is that when orc is facing left or right. the position of this inverses, this is to represent visibility. I want to see this with color blue.
///
/// The visibility shape should be used for detect if player is detected. and run that direction, or apply velocity in X and depending on the direciton orc is heading.
///
/// this will help us determine the state. where in alert mode. moves to the left 256 pixels, and changes the animation to run. then iddle.
///
/// the iddle is. Move > stop > flip direction, to detect player, if not, flip direction again and keep course another 256 pixels. searching.
///
/// if orc found player, move orc the same direction it found the player, changing the animation to run. once this happens it will enter ina while of dtecting enter battleZone.
///
/// this battle zone will be the used to do collision detection.and if orc, is in battle mode. add the orc and the player to the battle cycle. so they are both engaged.
///
/// if the player is not detected by the EyeSight rectangleshape of the orc. in battle mode, change to iddle mode. and then continue walking another 256.
///
/// there are 5 orcs per spawn point. 4 spawnpoints total becase we have a map of 3072 this is 6 times 512
///
/// so we have 2 spawn point across different main areas of battle. 
/// 
/// as soon as the orc is dead. reset everything. REmemeber the visibilty of orc should be as trasnparent sprite and a spawnpoint started position as the orc start position
///
/// only orc visible when is inGameMode. if not, visibility off and restart position. 
///
/// so I will provide 4 positions of x and y coordinate to spawn set as the intial position of spanw points and there for as the intiail position of orcs 
///
/// create part of the logic for battle mode
///
/// add in the resource manager the shape of the "Health" that will be a 2 shape one for the healthbarcontainer and other for healthbar
///
/// this will be anchored to orc position but with a variable called offset position. the width and the height of the bar should be by default 8 px height and container 10 pixels.
///
/// this will complete with the Orc class adition of funciton of show stats.. These stats should update after is getting damage to reflect it on there and if health = 0. change currentAnimationType to Die and after this anition endeds
///
/// set as OrcHasDied and this will trigger the reset function as we mentioned.
///
/// there should be a count for the OrcsSPawn in SpawnPoint. so if 5, it will no more spawn new orcs.
///
/// the idea is to keep track of how many MAx Enemies per spawn point are so when we save the progress with Shift + S it saves the player position and stats among with the inventory of player. and the current game level spawnpoints internal stats of the number of orcs spawn
///
/// and the position of the current in game spawn orc position in x and Y so when we Continue and laod it properly loads the progress of the game.
///
/// laoding the player location and life and stats and saving the spawnpoint data.
///
/// there is the win condition that entityt manger should be check if Crown class instance that has the sprite and shape if collision detection of player with crown, execute the get crown and displaye the win screen
///
/// duplicate  the game over GUI fucntions and change the game over to Congratulations! You won!
///
/// below that the same text of restart game.
///
/// 
///

