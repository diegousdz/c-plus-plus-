#include "Player.h"

// Initialize variables using the class constructor
Player::Player(std::string playerName, Inventory inventory)
{
    // initialize variables that are passed as parameters 
    name = playerName ;
    playerInventory = inventory;
    
    life = 1;
    health = 100.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    hasKingdomCrownInInventory = false;

    // Initialize player shape (16x16 pixels)
    shape.setSize(sf::Vector2f(16.0f, 16.0f));  
    shape.setTexture(&texturePlayer);  
    shape.setPosition(100, 100);

    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    spritePlayer = sf::Sprite();
}

void Player::setTexture(sf::Texture* texture)
{
    sf::Vector2u textureSize = texture->getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        std::cout << "Error: Texture is empty or not loaded properly!" << std::endl;
    } else
    {
        shape.setTexture(texture);
    }

    
}

void Player::setSize(float sizeX,float sizeY)
{
    shape.setSize(sf::Vector2f(sizeX, sizeY));
}

void Player::configureSprite( sf::Texture playerTexture )
{
    shape.setTexture(&playerTexture, false);
}

void Player::createPlayer(std::string incomingString, sf::Vector2f scaleVector)
{
    sf::Texture texture;
    texture.loadFromFile(incomingString);
    // Create a sprite
    spritePlayer.setTexture(texture);
    spritePlayer.setScale(scaleVector);
    spritePlayer.setColor(sf::Color(255, 255, 255, 200));
    spritePlayer.setPosition(100, 25);
}

Player::Player()
{
    name = "Unnamed"; // Default name
    life = 1;
    health = 100.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    hasKingdomCrownInInventory = false;

    
    // Initialize player shape (16x16 pixels)
    shape.setSize(sf::Vector2f(16.0f, 16.0f));  // Set the size of the player shape
    shape.setPosition(100, 100);                 // Initial position (you can adjust this)
    shape.setTexture(&texturePlayer);
    
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    spritePlayer = sf::Sprite();
}
