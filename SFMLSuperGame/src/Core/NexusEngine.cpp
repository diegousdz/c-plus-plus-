#include "NexusEngine.h"

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
        } else if(resourceManager.gameWin)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    resourceManager.gameWin = false;
                    resourceManager.winScreenInitialized = false;
                    game.restartGame(resourceManager.newGamePlayer, resourceManager);
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    resourceManager.gameWindow.close();
                }
            }
            return; 
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
                     
                        resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = true;  
                        resourceManager.newGamePlayer.isMoving = true;
                            resourceManager.setPlayerTypeOfAnimationLastSet(1);
                    } else
                    {
                        resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = true; 
                        resourceManager.newGamePlayer.isMoving = true;
                        resourceManager.setPlayerTypeOfAnimationLastSet(1);
                    }
                }
                else if (event.key.code == sf::Keyboard::D)  // Move right
                {
                    if(!resourceManager.newGamePlayer.isJumping)
                    {
                        resourceManager.setPlayerTypeOfAnimationLastSet(1);
                        resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
                    } else
                    {
                        resourceManager.setPlayerTypeOfAnimationLastSet(1);
                        resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                        resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                        resourceManager.newGamePlayer.isMoving = true;
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
                    
                    if (resourceManager.newGamePlayer.isOnGround) {
                        resourceManager.setPlayerTypeOfAnimationLastSet(Player::Idle);
                    }
                }

            if(resourceManager.newGamePlayer.isOnGround)
            {
                   // std::cout << "can jump is on ground" << std::endl;
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        resourceManager.newGamePlayer.velocity.y = -300.0f;  // Adjust jump strength as needed
                        resourceManager.newGamePlayer.isOnGround = false;   // Mark player as airborne.
                        resourceManager.newGamePlayer.isJumping = true;
                        resourceManager.setPlayerTypeOfAnimationLastSet(2);
                    }
            }else if (!resourceManager.newGamePlayer.isOnGround && resourceManager.newGamePlayer.velocity.y > 0)
             {
                 resourceManager.setPlayerTypeOfAnimationLastSet(3);  
             }
                if (event.key.code == sf::Keyboard::P)
                {
                    resourceManager.isMainMenuActive = !resourceManager.isMainMenuActive;  // Toggle the main menu
                }
            }
        }
    }
}

void NexusEngine::updatePlayerAnimation() {
    Player& player = resourceManager.newGamePlayer;
    
    if (player.isOnGround) {
        if (!player.isMoving) {
            resourceManager.setPlayerTypeOfAnimationLastSet(Player::Idle);
        }
    } else {
        if (player.velocity.y > 0) {
            resourceManager.setPlayerTypeOfAnimationLastSet(Player::Fall);
        }
        else if (player.velocity.y < 0) {
            resourceManager.setPlayerTypeOfAnimationLastSet(Player::Jump);
        }
    }
    
    if (player.isMoving) {
        resourceManager.setPlayerTypeOfAnimationLastSet(Player::Run);
    }
    
    player.setCurrentAction(static_cast<Player::AnimationType>(resourceManager.getPlayerTypeOfAnimationLastSet()));
}


void NexusEngine::update(float deltaTime)
{
    if(resourceManager.newGamePlayer.shape.getPosition().y >= resourceManager.deadZoneYPosition || resourceManager.newGamePlayer.life == 0 )
    {
        resourceManager.gameOver = true;
    }

    if (!resourceManager.isMainMenuActive && !resourceManager.gameWin)
    {
        game.checkForDoorsAndWinCondition(resourceManager.newGamePlayer, resourceManager);
    }
    
    if (resourceManager.isMainMenuActive)
    {
        if(!resourceManager.hasTexturesForGameLoaded)
        {
            resourceManager.loadGameBackgrounds();
        }
    } else {
        if (!resourceManager.gameOver && !resourceManager.gameWin) {
            game.update(deltaTime, resourceManager.newGamePlayer, resourceManager);
        
            if (!resourceManager.newGamePlayer.isOnGround)
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
            
            resourceManager.newGamePlayer.setCurrentAction(static_cast<Player::AnimationType>(resourceManager.getPlayerTypeOfAnimationLastSet()));
            
            resourceManager.newGamePlayer.updateAnimation(deltaTime);

            updatePlayerAnimation();
            
            if(resourceManager.newGamePlayer.life <= 0) {
                resourceManager.newGamePlayer.life = 0;
            }
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
            
            gameWindow.draw(resourceManager.newGamePlayer.shape);

            resourceManager.guiHandler.draw(gameWindow, resourceManager);

            if (resourceManager.gameWin) {
                  resourceManager.guiHandler.drawWinScreen(gameWindow, resourceManager);
            }
        } else if (resourceManager.gameOver) {
            resourceManager.guiHandler.drawGameOver(gameWindow, resourceManager);
        } 
    }

    gameWindow.display();
}

