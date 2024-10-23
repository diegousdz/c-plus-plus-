#include "NexusEngine.h"

void NexusEngine::init()
{
        resourceManager.loadResources();
}
void NexusEngine::update(float deltaTime)
{
        if(!resourceManager.isMainMenuActive)
        {
                if(!resourceManager.newGamePlayer.isMoving)
                {
            
                }
                resourceManager.newGamePlayer.shape.setPosition(static_cast<float>(resourceManager.windowWidth) / 2.0f, 96);
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
    
                // Update player position
                resourceManager.newGamePlayer.shape.move(resourceManager.newGamePlayer.velocity * deltaTime);

                // Check collision with the ground (simple example)
                if (resourceManager.newGamePlayer.shape.getPosition().y + resourceManager.newGamePlayer.shape.getSize().y > resourceManager.windowHeight) {
                        resourceManager.newGamePlayer.shape.setPosition(resourceManager.newGamePlayer.shape.getPosition().x, resourceManager.windowHeight - resourceManager.newGamePlayer.shape.getSize().y);
                        resourceManager.newGamePlayer.velocity.y = 0;
                        resourceManager.newGamePlayer.isOnGround = true;
                }
        }
}

void NexusEngine::draw(sf::RenderWindow &gameWindow)
{
        gameWindow.clear();  // Clear the window

        if (resourceManager.isMainMenuActive) {
                // Draw the main menu when it's active
                // drawMainMenu(gameWindow);
        } else {
                // Draw the player when the main menu is not active (gameplay state)
                // Game Loop
                if(!resourceManager.isGameInitialized)
                {
                      /*  if(gameProgressExist initGame();
                        createEnemiesLevelOne(); */
                        resourceManager.isGameInitialized = true;
                }
                resourceManager.newGamePlayer.shape.setPosition(static_cast<float>(resourceManager.windowWidth) / 2.0f, resourceManager.windowHeight / 2.0f); // Center the player in the window
                
                gameWindow.draw(resourceManager.newGamePlayer.shape);
                //  gameWindow.draw(newGamePlayer.spritePlayer);
                if(!resourceManager.newGamePlayer.isMoving)
                {
                        //   gameWindow.draw(resourceManagerInstance::spriteArrayIdleWithSword[0]);
                }

                /*
                for (int i = 0; i < 5; i++) {
                    gameWindow.draw(orcWarriorsPoolShapes[i].shape);
                } */
        }

        gameWindow.display();  // Display everything
}


void NexusEngine::handleInput()
{
        sf::Event event;
        while (resourceManager.gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        resourceManager.gameWindow.close();
                }
        
                // Handle main menu navigation
                if (resourceManager.isMainMenuActive) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                                resourceManager.currentOptionSelected--;
                                if (resourceManager.currentOptionSelected < 0)
                                        resourceManager.currentOptionSelected = 2;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                                resourceManager.currentOptionSelected++;
                                if (resourceManager.currentOptionSelected > 2)
                                        resourceManager.currentOptionSelected = 0;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                                if (resourceManager.currentOptionSelected == 0) {
                                        resourceManager.isMainMenuActive = false;
                                }
                        }
                } else {
                        // Handle player input for movement and actions
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                                resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                        } else {
                                resourceManager.newGamePlayer.velocity.x = 0;
                        }
                }
        }
}

void NexusEngine::initializeWindow(sf::RenderWindow gameWindow, int width, int height, std::string windowName)
{
        gameWindow.create(sf::VideoMode(width, height), "Stone & Frost");
    
}
