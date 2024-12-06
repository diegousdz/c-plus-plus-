#include "NexusManager.h"

void NexusManager::initializeWindow(sf::RenderWindow& gameWindow, int width, int height, std::string windowName) {
    gameWindow.create(sf::VideoMode(width, height), windowName);
}

void NexusManager::init() {
    resourceManager.loadResources();
    resourceManager.isGameInitialized = false;
    game = Game();
    resourceManager.guiHandler.gameOverInit(resourceManager);
    game.init(resourceManager.gameWindow, resourceManager, resourceManager.newGamePlayer);
}

void NexusManager::handleInput() {
    sf::Event event;
    while (resourceManager.gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
            resourceManager.gameWindow.close();
        }

        if (resourceManager.gameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    resourceManager.gameOver = false;
                    resourceManager.gameOverInitialized = false;
                    game.restartGame(resourceManager.newGamePlayer, resourceManager);
                } else if (event.key.code == sf::Keyboard::Escape) {
                    resourceManager.gameWindow.close();
                }
            }
        } else if (resourceManager.gameWin) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    resourceManager.gameWin = false;
                    resourceManager.winScreenInitialized = false;
                    game.restartGame(resourceManager.newGamePlayer, resourceManager);
                } else if (event.key.code == sf::Keyboard::Escape) {
                    resourceManager.gameWindow.close();
                }
            }
            return;
        }

        if (resourceManager.isMainMenuActive) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    do {
                        resourceManager.currentOptionSelected--;
                        if (resourceManager.currentOptionSelected < 0) {
                            resourceManager.currentOptionSelected = ResourceManager::maxItemsMenu - 1;
                        }
                    } while (!resourceManager.savedGameAvailable && resourceManager.currentOptionSelected == 1);
                }

                if (event.key.code == sf::Keyboard::S) {
                    do {
                        resourceManager.currentOptionSelected++;
                        if (resourceManager.currentOptionSelected >= ResourceManager::maxItemsMenu) {
                            resourceManager.currentOptionSelected = 0;
                        }
                    } while (!resourceManager.savedGameAvailable && resourceManager.currentOptionSelected == 1);
                }

                if (event.key.code == sf::Keyboard::Space) {
                    if (resourceManager.currentOptionSelected == 0) {
                        resourceManager.isMainMenuActive = false;
                        resourceManager.isInGame = true;
                    } else if (resourceManager.currentOptionSelected == 1) {
                        Player loadedPlayer = FileManager::loadPlayerProgress("saves", "player_save");
                        resourceManager.newGamePlayer = loadedPlayer;
                        resourceManager.newGamePlayer.loadAnimationsPlayer();
                        resourceManager.newGamePlayer.setTexture(&resourceManager.playerTexture);
                        resourceManager.isMainMenuActive = false;
                        resourceManager.isInGame = true;
                    } else if (resourceManager.currentOptionSelected == 2) {
                        resourceManager.gameWindow.close();
                    }
                }
            }
        } else {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    resourceManager.newGamePlayer.velocity.x = -resourceManager.newGamePlayer.speed;
                    resourceManager.newGamePlayer.onInverseDirection = true;
                    resourceManager.newGamePlayer.isMoving = true;
                    
                    if (resourceManager.newGamePlayer.isOnGround) {
              //          resourceManager.setPlayerTypeOfAnimationLastSet(Player::Run);
                        resourceManager.soundSequencer.playPlayerRunSound();
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                    resourceManager.newGamePlayer.onInverseDirection = false;
                    resourceManager.newGamePlayer.isMoving = true;
                    
                    if (resourceManager.newGamePlayer.isOnGround) {
               //         resourceManager.setPlayerTypeOfAnimationLastSet(Player::Run);
                        resourceManager.soundSequencer.playPlayerRunSound();
                    }
                } else if (event.key.code == sf::Keyboard::K && !resourceManager.newGamePlayer.isJumping) {
                    resourceManager.newGamePlayer.velocity.x = 0;
                    resourceManager.newGamePlayer.isMoving = false;
                    resourceManager.setPlayerTypeOfAnimationLastSet(4);
                    
                }

                if (event.key.code == sf::Keyboard::Space && resourceManager.newGamePlayer.isOnGround) {
                    resourceManager.setPlayerTypeOfAnimationLastSet(Player::Jump);
                    resourceManager.newGamePlayer.hasPlayerJump = false;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::K) {
                    resourceManager.newGamePlayer.velocity.x = 0;
                    resourceManager.newGamePlayer.isMoving = false;
                    resourceManager.soundSequencer.stopPlayerRunSound();
                    if (resourceManager.newGamePlayer.isOnGround && !resourceManager.newGamePlayer.hasPlayerJump && resourceManager.getPlayerTypeOfAnimationLastSet() != Player::Jump) {
                     //   resourceManager.setPlayerTypeOfAnimationLastSet(Player::Idle);
                    }
                }

                if (resourceManager.newGamePlayer.isOnGround) {
                    if (event.key.code == sf::Keyboard::Space) {
                        resourceManager.newGamePlayer.hasPlayerJump = true;
                        resourceManager.newGamePlayer.velocity.y = -400.0f;
                        resourceManager.newGamePlayer.isOnGround = false;
                        resourceManager.newGamePlayer.isJumping = true;
                        resourceManager.setPlayerTypeOfAnimationLastSet(2);
                        resourceManager.soundSequencer.playPlayerJumpSound();
                    }
                } else if (!resourceManager.newGamePlayer.isOnGround && resourceManager.newGamePlayer.velocity.y > 0) {
                    resourceManager.setPlayerTypeOfAnimationLastSet(3);
                }

                if (event.key.code == sf::Keyboard::P) {
                    resourceManager.isMainMenuActive = !resourceManager.isMainMenuActive;
                }
            }
        }
    }
}

void NexusManager::updatePlayerAnimation() {
    Player& player = resourceManager.newGamePlayer;
    if (player.isOnGround && !player.isMoving &&  resourceManager.getPlayerTypeOfAnimationLastSet() != Player::Jump) {
        resourceManager.setPlayerTypeOfAnimationLastSet(Player::Idle);
    } else {
        if (player.velocity.y > 0) {
            resourceManager.setPlayerTypeOfAnimationLastSet(Player::Fall);
        } else if (player.velocity.y < 0 && player.hasPlayerJump) {
            resourceManager.setPlayerTypeOfAnimationLastSet(Player::Jump);
        }
    }

    if (player.isMoving && player.isOnGround) {
        resourceManager.setPlayerTypeOfAnimationLastSet(Player::Run);
    }

    player.setCurrentAction(static_cast<Player::AnimationType>(resourceManager.getPlayerTypeOfAnimationLastSet()));
}

void NexusManager::update(float deltaTime) {
    if (resourceManager.newGamePlayer.shape.getPosition().y >= resourceManager.deadZoneYPosition || resourceManager.newGamePlayer.life == 0) {
        resourceManager.gameOver = true;
    }

    if (!resourceManager.isMainMenuActive && !resourceManager.gameWin) {
        game.checkForDoorsAndWinCondition(resourceManager.newGamePlayer, resourceManager);
    }

    if (resourceManager.isMainMenuActive) {
        if (!resourceManager.hasTexturesForGameLoaded) {
            resourceManager.loadGameBackgrounds();
        }
    } else {
        if (!resourceManager.gameOver && !resourceManager.gameWin) {
            game.update(deltaTime, resourceManager.newGamePlayer, resourceManager);
            if (!resourceManager.newGamePlayer.isOnGround) {
                resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;
            }  

            resourceManager.newGamePlayer.setCurrentAction(static_cast<Player::AnimationType>(resourceManager.getPlayerTypeOfAnimationLastSet()));
            resourceManager.newGamePlayer.updateAnimation(deltaTime);
            updatePlayerAnimation();

            if (resourceManager.newGamePlayer.life <= 0) {
                resourceManager.newGamePlayer.life = 0;
            }
        }
    }
}

void NexusManager::draw(sf::RenderWindow &gameWindow) {
    gameWindow.clear();

    if (resourceManager.isMainMenuActive) {
        resourceManager.guiHandler.setIsInGame(resourceManager, false);
        resourceManager.guiHandler.draw(gameWindow, resourceManager);
    } else {
        if (!resourceManager.gameOver) {
            resourceManager.guiHandler.setIsInGame(resourceManager, true);
            game.draw(gameWindow, resourceManager);
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