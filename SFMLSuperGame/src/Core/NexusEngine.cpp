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
    // --------------------------------------------------- check Main menu is not activated
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
            std::cout << "Shape Position: " << resourceManager.newGamePlayer.shape.getPosition().x << ", " << resourceManager.newGamePlayer.shape.getPosition().y << std::endl;
            std::cout << "Sprite Position: " << resourceManager.newGamePlayer.currentSprite.getPosition().x << ", " << resourceManager.newGamePlayer.currentSprite.getPosition().y << std::endl;

            game.update(deltaTime, resourceManager.newGamePlayer);
        
            // Apply gravity to the player when not on the ground
            if (!resourceManager.newGamePlayer.isOnGround)
            {
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
            }

            // Check if the player has landed on the ground or a platform
            float playerBottom = resourceManager.newGamePlayer.shape.getPosition().y + resourceManager.newGamePlayer.shape.getSize().y;
            if (playerBottom >= resourceManager.windowHeight) // Replace with platform collision detection
            {
                // Player hits the ground
                resourceManager.newGamePlayer.shape.setPosition(
                    resourceManager.newGamePlayer.shape.getPosition().x,
                    resourceManager.windowHeight - resourceManager.newGamePlayer.shape.getSize().y
                );
                resourceManager.newGamePlayer.velocity.y = 0; // Stop vertical movement
                resourceManager.newGamePlayer.isOnGround = true;
            }
            else
            {
                resourceManager.newGamePlayer.isOnGround = false; // Player is airborne
            }
        
            resourceManager.newGamePlayer.updateAnimation(deltaTime);

        
            // ----------------------------------------------------------- Animation Switch
        
            switch (resourceManager.getPlayerTypeOfAnimationLastSet()) {
            case 0:
                resourceManager.newGamePlayer.currentSprite.setTexture(resourceManager.playerIdleTexture);
                //     resourceManager.newGamePlayer.loadAnimations();
                // std::cout << "Switched to Idle Texture" << std::endl;
                break;
            case 1:
                resourceManager.newGamePlayer.currentSprite.setTexture(resourceManager.playerRunTexture);
                
                //    resourceManager.newGamePlayer.loadAnimations();
                //   std::cout << "Switched to Run Texture" << std::endl;
                break;
            case 2:

                resourceManager.newGamePlayer.currentSprite.setTexture(resourceManager.playerJumpTexture);
                //    resourceManager.newGamePlayer.loadAnimations();
                //    std::cout << "Switched to Jump Texture" << std::endl;
                break;
            default:  resourceManager.newGamePlayer.currentSprite.setTexture(resourceManager.playerIdleTexture);;
                resourceManager.newGamePlayer.loadAnimations();
            }
        
            /*
            // Check if the player is on the ground
            float playerBottom = resourceManager.newGamePlayer.shape.getPosition().y + resourceManager.newGamePlayer.shape.getSize().y;
            if (playerBottom >= static_cast<float>(resourceManager.windowHeight))
            {
                // Player hits the ground
                resourceManager.newGamePlayer.shape.setPosition(
                    resourceManager.newGamePlayer.shape.getPosition().x, 
                    static_cast<float>(resourceManager.windowHeight) - resourceManager.newGamePlayer.shape.getSize().y); // Remove extra semicolon
                resourceManager.newGamePlayer.velocity.y = 0;  // Stop vertical movement
                resourceManager.newGamePlayer.isOnGround = true;
                // Player is now on the ground
                if(resourceManager.isFirstFall)
                    resourceManager.isFirstFall = false;
                
                resourceManager.newGamePlayer.currentSprite.setPosition(
                    resourceManager.newGamePlayer.shape.getPosition()
                ); 
            } else
            {
                resourceManager.newGamePlayer.isOnGround = false;  // Player is airborne
            } */

    
            resourceManager.newGamePlayer.updateAnimation(deltaTime);
        }
    }
}
void NexusEngine::draw(sf::RenderWindow &gameWindow)
{
    gameWindow.clear();
    
        if (resourceManager.isMainMenuActive)
        {
            
            resourceManager.guiHandler.setIsInGame(resourceManager, false);
            resourceManager.guiHandler.draw(gameWindow, resourceManager);
        }
        else
        {
            if (!resourceManager.gameOver)
            {
                resourceManager.guiHandler.setIsInGame(resourceManager, true);
                game.draw(gameWindow, resourceManager );
                //  resourceManager.guiHandler.draw(gameWindow, resourceManager);
                sf::RectangleShape debugShape(sf::Vector2f(50.0f, 37.0f));
                debugShape.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
                debugShape.setPosition(resourceManager.newGamePlayer.shape.getPosition());
                gameWindow.draw(debugShape); 
            } else
            {
                /*
                if (!resourceManager.gameOverInitialized) {
                    resourceManager.guiHandler.gameOverInit(resourceManager);
                    resourceManager.gameOverInitialized = true;
                }
                resourceManager.guiHandler.drawGameOver(gameWindow, resourceManager); */
            }
        }
    if (resourceManager.gameOver) {
        resourceManager.guiHandler.drawGameOver(gameWindow, resourceManager);
    }
    
    gameWindow.display();
}

void NexusEngine::handleInput()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        resourceManager.setPlayerTypeOfAnimationLastSet(1); // Running left
    //    std::cout << "Running (left)" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        resourceManager.setPlayerTypeOfAnimationLastSet(1); // Running right
     //   std::cout << "Running (right)" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        resourceManager.setPlayerTypeOfAnimationLastSet(2); // Jumping
     //   std::cout << "Jumping" << std::endl;
    } else {
        resourceManager.setPlayerTypeOfAnimationLastSet(0); // Idle (no key pressed)
       // std::cout << "Idle" << std::endl;
    }
    
    sf::Event event;
    while (resourceManager.gameWindow.pollEvent(event))
    {
        // Close the window if the close event or Escape key is pressed
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        {
            resourceManager.gameWindow.close();
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

                if (event.key.code == sf::Keyboard::Space && resourceManager.newGamePlayer.isOnGround)
                {
                    resourceManager.newGamePlayer.velocity.y = -400.0f;  // Jump
                    resourceManager.newGamePlayer.isOnGround = false;  // Player is in the air
                    resourceManager.setPlayerTypeOfAnimationLastSet(2);
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

