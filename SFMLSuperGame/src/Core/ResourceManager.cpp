#include "ResourceManager.h"

void ResourceManager::allocateEnemies()
{
    // Allocate orcs for spawn manager one
    if(!hasSpawnOneInitialized)
    {
        for (int i = 0; i < 5; i++)
        {
            orcSpawnManagerOne[i] = new Orc();
            
            if (!orcSpawnManagerOne[i]->animationsLoaded)
            {
                // orcSpawnManagerOne[i]->loadAnimationsOrc();
            }
            
            orcSpawnManagerOne[i]->shape.setSize(sf::Vector2f(58.0f, 42.0f));
            orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);
            
        }
        hasSpawnOneInitialized = true;
    }

}

void ResourceManager::repositionEnemiesLevelOne(float initialPositionX, float initialPositionY)
{
    if(hasSpawnOneInitialized)
    {
        float spacing = orcSpawnManagerOne[0]->shape.getGlobalBounds().width + 20.0f;
        for (int i = 0; i < 5; i++)
        {
            if (orcSpawnManagerOne[i])
            {
                // HERE 
                orcSpawnManagerOne[i]->shape.setPosition(initialPositionX + (i * spacing), initialPositionY);
            }
        }
    }
}
void ResourceManager::loadResources()
{
    
    // Load the player's texture for placeholder (if needed)
    if (!playerTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player texture!" << std::endl;
    }

    // Load the player's idle texture
    if (!playerIdleTexture.loadFromFile("res/textures/Player/Tilemap/Idle/spritesheetIdle.png")) {
        std::cout << "Failed to load player idle texture!" << std::endl;
    }

    // Load the player's run texture
    if (!playerRunTexture.loadFromFile("res/textures/Player/Tilemap/Run/spritesheetRun.png")) {
        std::cout << "Failed to load player run texture!" << std::endl;
    }

    // Load the player's jump texture
    if (!playerJumpTexture.loadFromFile("res/textures/Player/Tilemap/Jump/spritesheetJump.png")) {
        std::cout << "Failed to load player jump texture!" << std::endl;
    }
    
    if (!playerAttack.loadFromFile("res/textures/Player/Tilemap/Attack/spritesheetAttack.png")) {
        std::cout << "Failed to load player jump texture!" << std::endl;
    }

    if (!heartTexture.loadFromFile("res/textures/gameplay/heart.png")) {
        std::cout << "Failed to load heart texture!" << std::endl;
    } else
    {
        std::cout << "Load heart texture!" << std::endl;
    }

    // Initialize the player with the loaded texture
    newGamePlayer.setTexture(&playerIdleTexture);

    // Load animations
    newGamePlayer.loadAnimationsPlayer();

    // You can also load other textures here (like for Orc, enemies, etc.)
    loadGameBackgrounds();
}

void ResourceManager::loadGameBackgrounds()
{
    if (!hasTexturesForGameLoaded) { 
        if (!backgroundOne.loadFromFile("res/textures/World/backgrounds/backgroundOne.png")) {
            std::cout << "FAILED to load bg 1 texture!" << std::endl;
        } else {
            backgroundOne.setSmooth(true);
            backgroundSpriteOne.setTexture(backgroundOne);  // Set the texture to backgroundOne
            backgroundSpriteOne.setPosition(0, 0);          // Position it at the origin
            hasTextureToSpriteOneFinished = true;
            std::cout << "bg 1 texture loaded!" << std::endl;

            // Debugging: Print out texture size to verify
            std::cout << "Background texture size: " 
                      << backgroundOne.getSize().x << "x" 
                      << backgroundOne.getSize().y << std::endl;
        }
        hasTexturesForGameLoaded = true;
    }
}



void ResourceManager::setDeltaTime()
{
     deltaTime = clock.restart().asSeconds();
}

float ResourceManager::getDeltaTime() const
{
    return deltaTime;
}



void ResourceManager::createEnemiesLevelOne(float initialPositionX, float initialPositionY)
{
    float spacing = orcSpawnManagerOne[0]->shape.getGlobalBounds().width + 20.0f; 

    // Position and initialize attributes for each Orc in the pool
    for (int i = 0; i < 5; i++)
    {
        if (orcSpawnManagerOne[i]) // Check if the orc exists
        {
            if(i == 1)
            {
                // Set initial position and attributes
                orcSpawnManagerOne[i]->shape.setPosition(310.219f, 66);
                orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 2)
            {
                // Set initial position and attributes
                orcSpawnManagerOne[i]->shape.setPosition(1024.0f, 128.0f);
                orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 3)
            {
                // Set initial position and attributes
                orcSpawnManagerOne[i]->shape.setPosition(2048, 66.0f);
                orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else if (i == 4)
            {
                // Set initial position and attributes
                orcSpawnManagerOne[i]->shape.setPosition(2422.99f, 128.0f);
                orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            } else 
            {
                // Set initial position and attributes
                orcSpawnManagerOne[i]->shape.setPosition(2870.32f, 128.0f);
                orcSpawnManagerOne[i]->shape.setFillColor(sf::Color::Red);  // Set color for the Orc
            }

        }
    }
}

int ResourceManager::getPlayerTypeOfAnimationLastSet() const {
    return playerTypeOfAnimationLastSet;
}

void ResourceManager::setPlayerTypeOfAnimationLastSet(int type) {
    playerTypeOfAnimationLastSet = type;
}

ResourceManager::~ResourceManager()
{
    // Clean up spawn manager orcs
    for (int i = 0; i < 5; i++)
    {
        delete orcSpawnManagerOne[i];
    }
    
    // Clean up level one pool orcs
    for (int i = 0; i < NUMBER_OF_ENEMY_LEVEL_ONE; i++)
    {
        delete orcWarriorsPoolShapes[i];
    }
}