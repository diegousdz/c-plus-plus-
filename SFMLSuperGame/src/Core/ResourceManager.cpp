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

    // Initialize the player with the loaded texture
    newGamePlayer.setTexture(&playerIdleTexture);

    // Load animations
    newGamePlayer.loadAnimations();

    // You can also load other textures here (like for Orc, enemies, etc.)
    loadGameBackgrounds();
}

void ResourceManager::loadGameBackgrounds()
{
    if (!hasTexturesForGameLoaded) { 
        if (!backgroundOne.loadFromFile("res/textures/World/backgrounds/backgroundOne.png")) {
            std::cout << "FAILED to load bg 1 texture!" << std::endl;
        } else {
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

Orc createOrc()
{
    Orc orcWarrior;
    
    orcWarrior.shape.setPosition(100, 0);
    
    orcWarrior.shape.setFillColor(sf::Color::Red);  // Orcs are red by default

    return orcWarrior;  // Return the created Orc
}

void ResourceManager::createEnemiesLevelOne()
{

        for (int i = 0; i < 5; i++)
        {
            Orc newOrc = createOrc();
            orcWarriorsPoolShapes[i] = newOrc;
            float xPosition = 50.0f + (i * 70); 
            float yPosition = windowHeight - newOrc.enemySize;            

            orcWarriorsPoolShapes[i].shape.setPosition(xPosition, yPosition);
        
            // TODD:  gameWindow.draw(orcWarriorsPoolShapes[i].shape);
        }
    
}

int ResourceManager::getPlayerTypeOfAnimationLastSet() const {
    return playerTypeOfAnimationLastSet;
}

void ResourceManager::setPlayerTypeOfAnimationLastSet(int type) {
    playerTypeOfAnimationLastSet = type;
}