#include "NexusEngine.h"

void NexusEngine::init()
{
    resourceManager.loadResources();
    resourceManager.isGameInitialized = true; 
}
void NexusEngine::update(float deltaTime)
{
    if (!resourceManager.isMainMenuActive)  // Only update when the game is active
    {
        
        // Apply gravity to the player when not on the ground
        resourceManager.newGamePlayer.velocity.y += resourceManager.newGamePlayer.gravity * deltaTime;

        // Update player position based on velocity (horizontal and vertical)
        resourceManager.newGamePlayer.shape.move(
            resourceManager.newGamePlayer.velocity.x * deltaTime, 
            resourceManager.newGamePlayer.velocity.y * deltaTime
        );

        // Check if the player is on the ground
        if (resourceManager.newGamePlayer.shape.getPosition().y + resourceManager.newGamePlayer.shape.getSize().y > resourceManager.windowHeight)
        {
            // Player hits the ground
            resourceManager.newGamePlayer.shape.setPosition(
                resourceManager.newGamePlayer.shape.getPosition().x, 
                resourceManager.windowHeight - resourceManager.newGamePlayer.shape.getSize().y
            );
            resourceManager.newGamePlayer.velocity.y = 0;  // Stop vertical movement
            resourceManager.newGamePlayer.isOnGround = true;  // Player is now on the ground
        }

        resourceManager.newGamePlayer.updateAnimation(deltaTime);
    }
}


void NexusEngine::drawMainMenu(sf::RenderWindow &window)
{
    window.clear(sf::Color(20, 12, 28));
    sf::Font font;
    if (!font.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Stone & Frost");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::White);
    title.setPosition(50, 50);

    const int max_items = 3;
    sf::Text menu[max_items];

    // Set up the menu items
    menu[0].setFont(font);
    menu[0].setCharacterSize(16);
    menu[0].setString("Start Game");
    menu[0].setPosition(sf::Vector2f(50, 180));

    menu[1].setFont(font);
    menu[1].setCharacterSize(16);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(50, 280));

    menu[2].setFont(font);
    menu[2].setCharacterSize(16);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(50, 380));

    window.draw(title);
    for (int i = 0; i < max_items; i++) {
        if (i == resourceManager.currentOptionSelected) {
            menu[i].setFillColor(sf::Color::Yellow);
        } else {
            menu[i].setFillColor(sf::Color::White);
        }
        window.draw(menu[i]);
    }

//    window.display();
}


void NexusEngine::draw(sf::RenderWindow &gameWindow)
{
    gameWindow.clear();

    if (resourceManager.isMainMenuActive)
    {
        drawMainMenu(gameWindow);
    }
    else
    {
        if (resourceManager.isGameInitialized)
        {
            // Draw test shape
       
            // Draw the player sprite
            gameWindow.draw(resourceManager.newGamePlayer.currentSprite);

            // Draw other game elements (enemies, etc.)
           /* for (int i = 0; i < 5; i++)
            {
                gameWindow.draw(resourceManager.orcWarriorsPoolShapes[i].shape);
            } */
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
                        resourceManager.currentOptionSelected = 2;  // Wrap to last item
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
                }
                else if (event.key.code == sf::Keyboard::D)  // Move right
                {
                    resourceManager.newGamePlayer.velocity.x = resourceManager.newGamePlayer.speed;
                    resourceManager.newGamePlayer.onInverseDirection = false;  // Set facing direction
                    resourceManager.newGamePlayer.isMoving = true;
                }
            }

            if (event.type == sf::Event::KeyReleased)  // Stop movement on key release
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
                {
                    resourceManager.newGamePlayer.velocity.x = 0;
                    resourceManager.newGamePlayer.isMoving = false;
                }

                if (event.key.code == sf::Keyboard::Space && resourceManager.newGamePlayer.isOnGround)
                {
                    resourceManager.newGamePlayer.velocity.y = -400.0f;  // Jump
                    resourceManager.newGamePlayer.isOnGround = false;  // Player is in the air
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

