#include "Player.h"

#include "../Core/ResourceManager.h"

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
    shape.setSize(sf::Vector2f(32.0f, 32.0f));
    shape.setTexture(&texturePlayer);
    shape.setPosition(100, 100);

    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSprite = sf::Sprite();
    loadAnimations();
    isMoving = false;
    onInverseDirection = false;
}

Player::Player()
{
    name = "Unnamed";  // Default name
    life = 1;
    health = 100.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    hasKingdomCrownInInventory = false;
    
    shape.setSize(sf::Vector2f(32.0f, 32.0f));
    shape.setPosition(100, 100);
    shape.setTexture(&texturePlayer);
    collisionShape.setSize(sf::Vector2f(50.0f, 32.0f));
    collisionShape.setFillColor(sf::Color(255, 0, 0, 128));
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSprite = sf::Sprite();
    loadAnimations();
    isMoving = false;
    onInverseDirection = false;
}

void Player::setPlayerPosition(sf::Vector2f incomingPosition)
{
    shape.setPosition(incomingPosition);
    sf::Vector2f shapeSize = shape.getSize();
    sf::Vector2f collisionSize = collisionShape.getSize();

    // Center collision shape based on player shape
    collisionShape.setPosition(
        incomingPosition.x + (shapeSize.x - collisionSize.x) / 2.0f,
        incomingPosition.y + (shapeSize.y - collisionSize.y) / 2.0f
    );

    // Set the sprite to match shape's position
    currentSprite.setPosition(incomingPosition);
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
 
// Handle player movement and update action (run, jump, idle, etc.)
void Player::handleMovement(float deltaTime)
{
    
    if (movingLeft)
    {
        onInverseDirection = true;
        velocity.x = -speed;
        currentAction = Run;
        isMoving = true;
        std::cout << "Player is moving left. currentAction: " << currentAction << std::endl;
    }
    else if (movingRight)
    {
        onInverseDirection = false;
        
        velocity.x = speed;
        currentAction = Run;
        isMoving = true;
        std::cout << "Player is moving right. currentAction: " << currentAction << std::endl;
    }
    
  
    shape.move(velocity * deltaTime);
    currentSprite.setPosition(shape.getPosition());
    /*else if (isOnGround) {  // Only set Idle if on the ground and not moving
        currentAction = Idle;
    }
        
    if (isJumping && isOnGround)
    {
        velocity.y = -200.0f;  // Reduced jump height (adjust value as needed)
        isOnGround = false;
        currentAction = Jump;
        isJumping = false;
    }

    // Apply gravity to control fall speed
    float gravityStrength = 800.0f;  // Adjust as needed to balance the fall rate
    velocity.y += gravityStrength * deltaTime;

    // Apply gravity
  //  velocity.y += gravity * deltaTime;

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
            std::cout << "Player landed and is idle. currentAction: " << currentAction << std::endl;
    }
    */
}


// Update the player's animation based on the current action
void Player::updateAnimation(float deltaTime)
{
    float horizontalPositionSprite = currentSprite.getPosition().x;
    float correctedPositionIfInverse = horizontalPositionSprite - shape.getPosition().x;
    
    if (animationClock.getElapsedTime().asSeconds() >= animationInterval)
    {
        animationClock.restart();

        // Get the total number of frames for the current action
        int totalFrames = spriteFramesPerTypeOfAnimation[currentAction];

        // Move to the next frame
        currentFrame = (currentFrame + 1) % totalFrames;

        // Get the current sprite based on the current action
        currentSprite = animSequencer.getCurrentSprite(currentAction, currentFrame);
        currentSprite.setPosition(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y);

        // Set position
        //currentSprite.setPosition(shape.getPosition());
        // Handle flipping based on movement direction
        // Flip the sprite if moving left and adjust position
        float frameWidth = currentSprite.getLocalBounds().width;
        const sf::IntRect& frameRect = animSequencer.getCurrentFrameRect(currentAction, currentFrame);

        
        if (onInverseDirection)
        {
            currentSprite.setScale(-1.f, 1.f);
            currentSprite.setOrigin(static_cast<float>(animSequencer.frameRect.width), 0.f);
        }
        else
        {
            currentSprite.setScale(1.f, 1.f);
            currentSprite.setPosition(shape.getPosition());
        }
    }
}
