#include "ResourceManager.h"

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

    if (!heartTexture.loadFromFile("res/textures/UI/heart.png")) {
        std::cout << "Failed to load heart texture!" << std::endl;
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
    float spacing = orcWarriorsPoolShapes[0]->shape.getGlobalBounds().width + 20.0f; 

    for (int i = 0; i < NUMBER_OF_ENEMY_LEVEL_ONE; i++)
    {
        orcWarriorsPoolShapes[i] = new Orc();

        if (!orcWarriorsPoolShapes[i]->animationsLoaded)
        {
            orcWarriorsPoolShapes[i]->loadAnimationsOrc();
        } else
        {
            orcWarriorsPoolShapes[i]->shape.setPosition(initialPositionX + (i * spacing), initialPositionY);
            orcWarriorsPoolShapes[i]->shape.setFillColor(sf::Color::Red);
        }
    }
}


int ResourceManager::getPlayerTypeOfAnimationLastSet() const {
    return playerTypeOfAnimationLastSet;
}

void ResourceManager::setPlayerTypeOfAnimationLastSet(int type) {
    playerTypeOfAnimationLastSet = type;
}