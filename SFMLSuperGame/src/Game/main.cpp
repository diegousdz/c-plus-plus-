#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "./../GameEntities/Player.h"
#include "./../Core/FileManager.h"
#include "StoneAndFrostWorld.h"
#include "./../GameEntities/Orc.h"
#include "./../Core/ResourceManager.h"
#include "./../Core/NexusEngine.h"


using namespace std;
// Global constants for window properties
const string windowTitle = "Stone & Frost";




bool isUsingGamepad = false;

int currentOptionSelected = 0;
bool SetValueOnce = false;
bool isGameInitialized = false;
sf::Sprite mySprite;

Orc orcWarriorsPoolShapes[5];
ResourceManager resourceManagerInstance;
/*
struct Score
{
    string name;
    int score;
    Score(std::string playerName = "", int playerScore = 0)
       : name(playerName), score(playerScore) {}
}; */



void  startGameLevelOne(sf::RenderWindow &window)
{
    if(!isGameInitialized) {}
}

void drawMainMenu(sf::RenderWindow &window)
{
    window.clear(sf::Color(20, 12, 28));
    sf::Font font;
    if(!font.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
    {
        cout << "Error loading arial.ttf" << endl;
    }

    sf::Text title;
    title.setFont(font);  // Set the loaded arcade font
    title.setString("Stone & Frost");  // Set the text
    title.setCharacterSize(32);  // Set the size of the text (pixel perfect fonts may need adjustments)
    title.setFillColor(sf::Color::White);  // Set the color of the text
    title.setPosition(50, 50);  // Set the position of the text

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
        if (i == currentOptionSelected) {
            menu[i].setFillColor(sf::Color::Yellow); // Highlight selected option
        } else {
            menu[i].setFillColor(sf::Color::White);
        }
        window.draw(menu[i]);
    }
    
}





/*
void initGame()
{
    
    // Initialize the StoneAndFrostWorld with screen width and height
  //  initializeWindow(windowWidth, windowHeight);
    
  //  newGamePlayer.shape.setSize(playerSize);
   // newGamePlayer.spritePlayer.setScale(playerSize);
   /*
     newGamePlayer.shape.setFillColor(sf::Color::Red);
     newGamePlayer.shape.setPosition(320,240);
    
    sf::Texture texturePlayer;
    initializeWindow(windowWidth, windowHeight);

    // Set player size and sprite properties
    sf::Vector2<float> playerSize = sf::Vector2f(50.0, 37.0);
    newGamePlayer.shape.setSize(playerSize);
    newGamePlayer.spritePlayer.setScale(1.0f, 1.0f);  // Reset scale

    // if you cant find the texture. do a console message otherwise  Load texture for the player
    if (!newGamePlayer.texturePlayer.loadFromFile("res/textures/Player/idleWithSword/adventurer-idle-2-00.png")) {
        std::cout << "Error loading player texture" << std::endl;
    } else {
        // Set the texture if loading is successful
        newGamePlayer.shape.setTexture(&newGamePlayer.texturePlayer);
    //    newGamePlayer.setTexture(newGamePlayer.tex)
    }
*/
    // Set sprite position
 //   mySprite.setPosition(windowWidth / 2.0f, 96);
/*
    if (!newGamePlayer.texturePlayer.loadFromFile("res/textures/Player/idleWithSword/adventurer-idle-2-00.png")) {
        std::cout << "Error loading player texture" << std::endl;
    } else {
        std::cout << "Texture size: " << newGamePlayer.texturePlayer.getSize().x << " x " 
                  << newGamePlayer.texturePlayer.getSize().y << std::endl;
        newGamePlayer.shape.setTexture(&newGamePlayer.texturePlayer);  // Bind texture
        sf::Vector2f playerSize(50.0f, 37.0f); // This matches the texture's size
        newGamePlayer.shape.setSize(playerSize); // Ensure the shape has a size
        newGamePlayer.shape.setTexture(&newGamePlayer.texturePlayer);
    }
    //newGamePlayer.shape.setPosition(windowWidth / 2.0f, windowHeight - newGamePlayer.shape.getSize().y);  // Start at the center of the screen
    newGamePlayer.shape.setPosition(windowWidth - 2.0f, windowHeight - newGamePlayer.shape.getSize().y);

 //   newGamePlayer.spritePlayer.setPosition(windowWidth / 2.0f, windowHeight - newGamePlayer.shape.getSize().y);
    
    // Check if save file exists
    /*
    std::ifstream checkFile("res/data/PlayerProgress.dat");
    if (checkFile.good()) {
        // Load existing player progress
        newGamePlayer = FileManager::loadPlayerProgress("res/data", "PlayerProgress");
        std::cout << "Loaded player: " << newGamePlayer.name << std::endl;
    } else {
        // Create a new player with default attributes
        Inventory defaultInventory;
        newGamePlayer = Player("Kaleb", defaultInventory);
        newGamePlayer.setSize(500.0f,37.0f);
        StoneAndFrostWorld world(windowWidth, windowHeight);
        std::cout << "Initialize Game Function Called " << std::endl;
    }
    checkFile.close(); 
} */
/*
void InputKeyboard(sf::RenderWindow& gameWindow, Player& player)
{
    // create an event
    sf::Event event;

    //a while loop that listen to the event
    while (gameWindow.pollEvent(event))
    {
        // if the event is closed or escape key
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            //save game
            FileManager::savePlayerProgress("res/data", "PlayerProgress", newGamePlayer);
            // close program
            gameWindow.close();
        }

        if(isMainMenuActive)
        {if (!SetValueOnce)  // Only change the selection if SetValueOnce is false
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                currentOptionSelected--;
                if (currentOptionSelected < 0) {
                    currentOptionSelected = 2;  // Wrap around to the last item
                }
                SetValueOnce = true;  // Prevent further changes until key is released
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                currentOptionSelected++;
                if (currentOptionSelected > 2) {
                    currentOptionSelected = 0;  // Wrap around to the first item
                }
                SetValueOnce = true;  // Prevent further changes until key is released
            }
        }

            // When no movement keys are pressed, reset SetValueOnce
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                SetValueOnce = false;  // Allow selection to change on the next key press
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if(currentOptionSelected == 0)
                {
                    isMainMenuActive = false;
                }
            }
            
        } else
        {
            // Handle left/right movement with A/D keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player.velocity.x = -player.speed;  // Move left
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.velocity.x = player.speed;   // Move right
            } else {
                    player.velocity.x = 0;  // Stop horizontal movement when no key is pressed
            }

            // Handle jumping with Space key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.isOnGround) {
                player.velocity.y = -player.speed;  // Jump
                player.isOnGround = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                std::cout << "P is pressed" << "\n";
                isMainMenuActive = !isMainMenuActive;
            }
           
        }
      
    }
} */

void Update(Player& player, float deltaTime) {
    // Gravity
   /* if(!re.isMainMenuActive)
    {
        if(!newGamePlayer.isMoving)
        {
            
        }
        player.shape.setPosition(windowWidth / 2.0f, 96);
        player.velocity.y += player.gravity * deltaTime;
    
        // Update player position
        player.shape.move(player.velocity * deltaTime);

        // Check collision with the ground (simple example)
        if (player.shape.getPosition().y + player.shape.getSize().y > windowHeight) {
            player.shape.setPosition(player.shape.getPosition().x, windowHeight - player.shape.getSize().y);
            player.velocity.y = 0;
            player.isOnGround = true;
        }
    }*/

}


/*
std::string scoreToString(const Score& score) {
    return "Name: " + score.name + "\nScore: " + std::to_string(score.score) + "\n";
} */

int main()
{
    NexusEngine& engine = NexusEngine::getInstance();
    engine.init();
    
    sf::Clock clock;
    while (engine.getResourceManager().gameWindow.isOpen())
    {
        engine.getResourceManager().setDeltaTime();
        engine.handleInput();
        engine.update(engine.getResourceManager().getDeltaTime());
     //   engine.draw(engine.getResourceManager().gameWindow);
    }

    return 0;
}
