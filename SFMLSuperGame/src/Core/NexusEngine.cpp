﻿#include "NexusEngine.h"

void NexusEngine::initializeWindow(sf::RenderWindow& gameWindow, int width, int height, std::string windowName)
{
    gameWindow.create(sf::VideoMode(width, height), windowName);
}

void NexusEngine::init()
{
    resourceManager.loadResources();
    resourceManager.isGameInitialized = false;
    game = Game();
    resourceManager.guiHandler.gameOverInit(resourceManager);
    game.init(resourceManager.gameWindow, resourceManager, resourceManager.newGamePlayer);
}

void NexusEngine::handleInput()
{
    sf::Event event;
    while (resourceManager.gameWindow.pollEvent(event))
    {
        
        // Close the window if the close event or Escape key is pressed
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        {
            resourceManager.gameWindow.close();
        }

        if(resourceManager.gameOver)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    resourceManager.gameOver = false;
                    resourceManager.gameOverInitialized = false;
                    game.restartGame(resourceManager.newGamePlayer, resourceManager);
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    // Player pressed Escape to exit the game
                    resourceManager.gameWindow.close();
                }
            }
        }
        // Handle main menu navigation
        if (resourceManager.isMainMenuActive)
        {
            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::W)  // Up
                {
                    do {
                        resourceManager.currentOptionSelected--;
                        if (resourceManager.currentOptionSelected < 0)
                        {
                            resourceManager.currentOptionSelected = ResourceManager::maxItemsMenu - 1;
                        }
                    } while (!resourceManager.savedGameAvailable && resourceManager.currentOptionSelected == 1);
                }

                if (event.key.code == sf::Keyboard::S)  // Down
                {
                    do {
                        resourceManager.currentOptionSelected++;
                        if (resourceManager.currentOptionSelected >= ResourceManager::maxItemsMenu)
                        {
                            resourceManager.currentOptionSelected = 0;  
                        }
                    } while (!resourceManager.savedGameAvailable && resourceManager.currentOptionSelected == 1);
                }

                // Handle selecting the current option
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (resourceManager.currentOptionSelected == 0)  
                    {
                        resourceManager.isMainMenuActive = false;
                        resourceManager.isInGame = true;
                    }else if (resourceManager.currentOptionSelected == 1)  
                    {
                        // Load Gamer
                        Player loadedPlayer = FileManager::loadPlayerProgress("saves", "player_save");
                        resourceManager.newGamePlayer = loadedPlayer;

                        // Reinitialize necessary components
                        resourceManager.newGamePlayer.loadAnimationsPlayer();
                        
                  //      resourceManager.enemyLevelManager.loadAnimationsOrc();
                        
                        resourceManager.newGamePlayer.setTexture(&resourceManager.playerTexture);

                        resourceManager.isMainMenuActive = false;
                        resourceManager.isInGame = true;
                    }
                    else if (resourceManager.currentOptionSelected == 2)  
                    {
                        resourceManager.gameWindow.close();  
                    }
                }
            }
        }
        else
        {
            // Handle player input for movement and jumping
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)  // Move left
                {
                    if(!resourceManager.newGamePlayer.isJumping)
                    {
                        resourceManager.newGamePlayer.velocity.y = resourceManager.newGamePlayer.gravity;
                        resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = true;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
                            resourceManager.setPlayerTypeOfAnimationLastSet(1);
                    } else
                    {
                        resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = true;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
                            resourceManager.setPlayerTypeOfAnimationLastSet(3);
                    }
                }
                else if (event.key.code == sf::Keyboard::D)  // Move right
                {
                    if(!resourceManager.newGamePlayer.isJumping)
                    {
                        resourceManager.newGamePlayer.velocity.y = resourceManager.newGamePlayer.gravity;
                        resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
                        
              
                            resourceManager.setPlayerTypeOfAnimationLastSet(1 );
                        
                    } else
                    {
                        resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
                       
                            resourceManager.setPlayerTypeOfAnimationLastSet(3);
                    }
                } else if  (event.key.code == sf::Keyboard::K && !resourceManager.newGamePlayer.isJumping)  // Attack
                {
                    if(!resourceManager.newGamePlayer.onInverseDirection){
                        resourceManager.newGamePlayer.velocity.x = 0;
                        resourceManager.newGamePlayer.onInverseDirection = false;  
                        resourceManager.newGamePlayer.isMoving = false;
                        resourceManager.setPlayerTypeOfAnimationLastSet(4);
                    } else { 
                        resourceManager.newGamePlayer.velocity.x = 0;
                        resourceManager.newGamePlayer.onInverseDirection = true; 
                        resourceManager.newGamePlayer.isMoving = false;
                        resourceManager.setPlayerTypeOfAnimationLastSet(4);
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased)  // Stop movement on key release
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::K)
                {
                    resourceManager.newGamePlayer.velocity.x = 0;
                    resourceManager.newGamePlayer.isMoving = false;
                    resourceManager.setPlayerTypeOfAnimationLastSet(0);
                }

            if(resourceManager.newGamePlayer.isOnGround)
            {
                    std::cout << "can jump is on ground" << std::endl;
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        resourceManager.newGamePlayer.velocity.y = -400.0f;  // Adjust jump strength as needed
                        resourceManager.newGamePlayer.isOnGround = false;   // Mark player as airborne.
                        resourceManager.newGamePlayer.isJumping = true;
                        resourceManager.setPlayerTypeOfAnimationLastSet(2);
                    }
            }else if (!resourceManager.newGamePlayer.isOnGround && resourceManager.newGamePlayer.velocity.y > 0)
             {
                 // If we're falling, transition to fall animation
                 resourceManager.setPlayerTypeOfAnimationLastSet(3);  // Fall
             }

               // if (resourceManager.newGamePlayer.isOnGround && )

                // Toggle main menu with 'P'
                if (event.key.code == sf::Keyboard::P)
                {
                    resourceManager.isMainMenuActive = !resourceManager.isMainMenuActive;  // Toggle the main menu
                }
            }
        }
    }
}

void NexusEngine::update(float deltaTime)
{

    if(resourceManager.newGamePlayer.shape.getPosition().y >= resourceManager.deadZoneYPosition || resourceManager.newGamePlayer.life == 0)
    {
        resourceManager.gameOver = true;
    }
    
    if (resourceManager.isMainMenuActive)
    {
        if(!resourceManager.hasTexturesForGameLoaded)
        {
            resourceManager.loadGameBackgrounds();
        }
    }
    else
    {
        if (!resourceManager.gameOver) {

            game.update(deltaTime, resourceManager.newGamePlayer, resourceManager);
        
            if (!resourceManager.newGamePlayer.isOnGround)
            {
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
            }
            
            resourceManager.newGamePlayer.setCurrentAction(static_cast<Player::AnimationType>(resourceManager.getPlayerTypeOfAnimationLastSet()));
        
            // ----------------------------------------------------------- Animation Switch
            /*
            switch (resourceManager.getPlayerTypeOfAnimationLastSet()) {
            case 0:
                resourceManager.newGamePlayer.currentSpritePlayer.setTexture(resourceManager.playerIdleTexture);
                //     resourceManager.newGamePlayer.loadAnimations();
                // std::cout << "Switched to Idle Texture" << std::endl;
                break;
            case 1:
                resourceManager.newGamePlayer.currentSpritePlayer.setTexture(resourceManager.playerRunTexture);
                
                //    resourceManager.newGamePlayer.loadAnimations();
                //   std::cout << "Switched to Run Texture" << std::endl;
                break;
            case 2:

                resourceManager.newGamePlayer.currentSpritePlayer.setTexture(resourceManager.playerJumpTexture);
                //    resourceManager.newGamePlayer.loadAnimations();
                //    std::cout << "Switched to Jump Texture" << std::endl;
                break;

            case 3:
                resourceManager.newGamePlayer.currentSpritePlayer.setTexture(resourceManager.playerAttack);
                //    resourceManager.newGamePlayer.loadAnimations();
                //    std::cout << "Switched to Jump Texture" << std::endl;
                break;
            default:  resourceManager.newGamePlayer.currentSpritePlayer.setTexture(resourceManager.playerIdleTexture);;
                resourceManager.newGamePlayer.loadAnimationsPlayer();
            }
            */
            
            resourceManager.newGamePlayer.updateAnimation(deltaTime);
        }
    }
}

void NexusEngine::draw(sf::RenderWindow &gameWindow) {
    gameWindow.clear();
    
    if (resourceManager.isMainMenuActive) {
        resourceManager.guiHandler.setIsInGame(resourceManager, false);
        resourceManager.guiHandler.draw(gameWindow, resourceManager);
    } else {
        if (!resourceManager.gameOver) {
            resourceManager.guiHandler.setIsInGame(resourceManager, true);
            game.draw(gameWindow, resourceManager);

            resourceManager.newGamePlayer.shape.setFillColor(sf::Color(255, 0, 0, 128)); // Red with transparency
            gameWindow.draw(resourceManager.newGamePlayer.shape);

            resourceManager.newGamePlayer.shape.setFillColor(sf::Color(255, 0, 0, 128)); // Red with transparency
            gameWindow.draw(resourceManager.newGamePlayer.shape);

            // Debug: Draw Player's Sprite (Blue)
            sf::RectangleShape spriteDebugBox;
            spriteDebugBox.setSize(sf::Vector2f(
                resourceManager.newGamePlayer.currentSpritePlayer.getGlobalBounds().width,
                resourceManager.newGamePlayer.currentSpritePlayer.getGlobalBounds().height));
            spriteDebugBox.setPosition(resourceManager.newGamePlayer.currentSpritePlayer.getPosition());
            spriteDebugBox.setFillColor(sf::Color(0, 0, 255, 128)); // Blue with transparency
            gameWindow.draw(spriteDebugBox);

            // Debug: Draw Collision Shape (Green)
            resourceManager.newGamePlayer.collisionShape.setFillColor(sf::Color(0, 255, 0, 128)); // Green with transparency
            gameWindow.draw(resourceManager.newGamePlayer.collisionShape);
            resourceManager.guiHandler.draw(gameWindow, resourceManager);

                // Debug Output to Console
            /*    std::cout << "Player Shape - Position: (" << resourceManager.newGamePlayer.shape.getPosition().x
                          << ", " << resourceManager.newGamePlayer.shape.getPosition().y
                          << "), Size: (" << resourceManager.newGamePlayer.shape.getSize().x
                          << ", " << resourceManager.newGamePlayer.shape.getSize().y << ")" << std::endl;

                std::cout << "Player Sprite - Position: (" << resourceManager.newGamePlayer.currentSpritePlayer.getPosition().x
                          << ", " << resourceManager.newGamePlayer.currentSpritePlayer.getPosition().y
                          << "), Size: (" << spriteDebugBox.getSize().x
                          << ", " << spriteDebugBox.getSize().y << ")" << std::endl;

                std::cout << "Collision Shape - Position: (" << resourceManager.newGamePlayer.collisionShape.getPosition().x
                          << ", " << resourceManager.newGamePlayer.collisionShape.getPosition().y
                          << "), Size: (" << resourceManager.newGamePlayer.collisionShape.getSize().x
                          << ", " << resourceManager.newGamePlayer.collisionShape.getSize().y << ")" << std::endl; */

        } else {
            if (resourceManager.gameOver) {
                resourceManager.guiHandler.drawGameOver(gameWindow, resourceManager);
            }
        }
    }


    gameWindow.display();
}

