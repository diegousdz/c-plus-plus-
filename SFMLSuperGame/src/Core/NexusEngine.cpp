#include "NexusEngine.h"


void NexusEngine::init()
{
    resourceManager.loadResources();
    resourceManager.isGameInitialized = false;
    game = Game();
    resourceManager.guiHandler.gameOverInit(resourceManager);
    game.init(resourceManager.gameWindow, resourceManager, resourceManager.newGamePlayer);
}

void NexusEngine::update(float deltaTime)
{

    if(resourceManager.newGamePlayer.shape.getPosition().y >= resourceManager.deadZoneYPosition)
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

            game.update(deltaTime, resourceManager.newGamePlayer);
        
            // Apply gravity to the player when not on the ground
            if (!resourceManager.newGamePlayer.isOnGround)
            {
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
            }

        
            // ----------------------------------------------------------- Animation Switch
        
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

            // Draw the debug bounding box around the player for collision detection
            sf::RectangleShape debugShape(sf::Vector2f(50.0f, 37.0f));  // Adjust size as needed
            debugShape.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
            debugShape.setPosition(resourceManager.newGamePlayer.shape.getPosition());
            gameWindow.draw(debugShape);
        } else {
            if (resourceManager.gameOver) {
                resourceManager.guiHandler.drawGameOver(gameWindow, resourceManager);
            }
        }
    }

    gameWindow.display();
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
                    // Player pressed Spacebar to restart the game
                   // restartGame();
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
            if (event.type == sf::Event::KeyPressed)  // Only trigger on key press
            {
                if (event.key.code == sf::Keyboard::W)  // Up
                {
                    resourceManager.currentOptionSelected--;
                    if (resourceManager.currentOptionSelected < 0)
                    {
                        resourceManager.currentOptionSelected = 2;
                    // Wrap to last item
                    }
                }

                if (event.key.code == sf::Keyboard::S)  // Down
                {
                    resourceManager.currentOptionSelected++;
                    if (resourceManager.currentOptionSelected > 2)
                    {
                        resourceManager.currentOptionSelected = 0;  // Wrap to first item
                    }
                }

                // Handle selecting the current option
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (resourceManager.currentOptionSelected == 0)  // Start Game
                    {
                        resourceManager.isMainMenuActive = false;  // Exit the menu
                    }
                    else if (resourceManager.currentOptionSelected == 2)  // Exit
                    {
                        resourceManager.gameWindow.close();  // Close the game
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
                    resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                    resourceManager.newGamePlayer.onInverseDirection = true;  // Set facing direction
                    resourceManager.newGamePlayer.isMoving = true;
                    resourceManager.setPlayerTypeOfAnimationLastSet(1);
                }
                else if (event.key.code == sf::Keyboard::D)  // Move right
                {
                    resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                    resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                    resourceManager.newGamePlayer.isMoving = true;
                    resourceManager.setPlayerTypeOfAnimationLastSet(1);
                }
            }

            if (event.type == sf::Event::KeyReleased)  // Stop movement on key release
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
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
                        resourceManager.newGamePlayer.isOnGround = false;   // Mark player as airborne
                        resourceManager.setPlayerTypeOfAnimationLastSet(2);
                    }
                }
                

                // Toggle main menu with 'P'
                if (event.key.code == sf::Keyboard::P)
                {
                    resourceManager.isMainMenuActive = !resourceManager.isMainMenuActive;  // Toggle the main menu
                }
            }
        }
    }
}


void NexusEngine::initializeWindow(sf::RenderWindow& gameWindow, int width, int height, std::string windowName)
{
        gameWindow.create(sf::VideoMode(width, height), windowName);
}

