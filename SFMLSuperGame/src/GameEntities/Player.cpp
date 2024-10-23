#include "Player.h"

// New function to load animations
void Player::loadAnimations()
{
    // Frame dimensions (assuming all frames are the same size)
    int frameWidth = 50;  // Adjust based on your spritesheet
    int frameHeight = 37; // Adjust based on your spritesheet

    // Load Idle animation frames
    animSequencer.loadAnimationFrames(
        Idle,
        "res/textures/Player/Tilemap/Idle/spritesheetIdle.png",
        spriteFramesPerTypeOfAnimation[Idle],
        frameWidth,
        frameHeight
    );

    // Load Run animation frames
    animSequencer.loadAnimationFrames(
        Run,
        "res/textures/Player/Tilemap/Run/spritesheetRun.png",
        spriteFramesPerTypeOfAnimation[Run],
        frameWidth,
        frameHeight
    );

    // Repeat for other animations (Jump, Fall, Attack, Die)
}

// Initialize variables using the class constructor
Player::Player(std::string playerName, Inventory inventory)
{
    name = playerName;
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
    currentSprite = sf::Sprite();
    loadAnimations();
}

Player::Player()
{
    name = "Unnamed";  // Default name
    life = 1;
    health = 100.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    hasKingdomCrownInInventory = false;

    // Initialize player shape (16x16 pixels)
    shape.setSize(sf::Vector2f(16.0f, 16.0f));
    shape.setPosition(100, 100);
    shape.setTexture(&texturePlayer);
    
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSprite = sf::Sprite();
    loadAnimations();
}

// Set texture for the player
void Player::setTexture(sf::Texture* texture)
{
    sf::Vector2u textureSize = texture->getSize();
    if (textureSize.x == 0 || textureSize.y == 0)
    {
        std::cout << "Error: Texture is empty or not loaded properly!" << std::endl;
    }
    else
    {
        shape.setTexture(texture);
    }
}

// Set size of the player shape
void Player::setSize(float sizeX, float sizeY)
{
    shape.setSize(sf::Vector2f(sizeX, sizeY));
}

// Configure the player sprite with a texture
void Player::configureSprite(sf::Texture playerTexture)
{
    shape.setTexture(&playerTexture, false);
}

// Create the player using a texture file and scale
void Player::createPlayer(std::string incomingString, sf::Vector2f scaleVector)
{
    sf::Texture texture;
    if (!texture.loadFromFile(incomingString))
    {
        std::cout << "Failed to load texture: " << incomingString << std::endl;
    }
    else
    {
        currentSprite.setTexture(texture);
        currentSprite.setScale(scaleVector);
        currentSprite.setColor(sf::Color(255, 255, 255, 200));
        currentSprite.setPosition(100, 25);
    }
}

// Handle player movement and update action (run, jump, idle, etc.)
void Player::handleMovement(float deltaTime)
{
    if (movingLeft)
    {
        velocity.x = -speed;
        onInverseDirection = true;
        currentAction = Run;
        isMoving = true;
    }
    else if (movingRight)
    {
        velocity.x = speed;
        onInverseDirection = false;
        currentAction = Run;
        isMoving = true;
    }
    else
    {
        velocity.x = 0;
        if (isOnGround)
            currentAction = Idle;
    }

    if (isJumping && isOnGround)
    {
        velocity.y = -400.0f;
        isOnGround = false;
        currentAction = Jump;
        isJumping = false; // Reset jumping flag
    }

    // Apply gravity
    velocity.y += gravity * deltaTime;

    // Update position
    shape.move(velocity * deltaTime);

    // Update sprite position
    currentSprite.setPosition(shape.getPosition());

    // Check for landing
    if (shape.getPosition().y >= 500)
    {
        isOnGround = true;
        velocity.y = 0;
        shape.setPosition(shape.getPosition().x, 500);
        if (!isMoving)
            currentAction = Idle;
    }
}


// Update the player's animation based on the current action
void Player::updateAnimation(float deltaTime)
{
    if (animationClock.getElapsedTime().asSeconds() >= animationInterval)
    {
        animationClock.restart();

        // Get the total number of frames for the current action
        int totalFrames = spriteFramesPerTypeOfAnimation[currentAction];

        // Move to the next frame
        currentFrame = (currentFrame + 1) % totalFrames;

        // Get the current sprite based on the current action
        currentSprite = animSequencer.getCurrentSprite(currentAction, currentFrame);

        // Set position
        currentSprite.setPosition(shape.getPosition());

        // Handle flipping based on movement direction
        if (onInverseDirection)
        {
            currentSprite.setScale(-1.f, 1.f); // Flip sprite for left movement
        }
        else
        {
            currentSprite.setScale(1.f, 1.f); // Default scale for right movement
        }
    }
}
