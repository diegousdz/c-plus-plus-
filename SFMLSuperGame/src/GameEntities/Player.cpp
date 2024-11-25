#include "Player.h"
#include "../Core/ResourceManager.h"

Player::Player(std::string playerName, Inventory inventory) : Warrior(100, 20)
{
    name = playerName;
    playerInventory = inventory;
    
    life = 3;
    health = 100.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    hasKingdomCrownInInventory = false;
    
    shape.setSize(sf::Vector2f(50.0f, 37.0f));
    shape.setTexture(&texturePlayer);
    shape.setPosition(100, 100);

    collisionShape.setSize(sf::Vector2f(50.0f, 37.0f));

    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSpritePlayer = sf::Sprite();
    loadAnimationsPlayer();
    isMoving = false;
    onInverseDirection = false;
}

Player::Player() : Warrior(100, 20)
{
    name = "Kael";

    playerInventory = Inventory();
    
    hasKingdomCrownInInventory = false;;
    life = 3;
    health = 48.0f;
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
    currentSpritePlayer = sf::Sprite();
    loadAnimationsPlayer();
    isMoving = false;
    onInverseDirection = false;
}

void Player::loadAnimationsPlayer()
{
    int frameWidth = 50;  
    int frameHeight = 37;
    
    
    animSequencerPlayer.loadAnimationFrames(
        Idle,
        "res/textures/Player/Tilemap/Idle/spritesheetIdle.png",
        spriteFramesPerTypeOfAnimationPlayer[Idle],
        frameWidth,
        frameHeight
    );
    
    animSequencerPlayer.loadAnimationFrames(
        Run,
        "res/textures/Player/Tilemap/Run/spritesheetRun.png",
        spriteFramesPerTypeOfAnimationPlayer[Run],
        frameWidth,
        frameHeight
    );

    animSequencerPlayer.loadAnimationFrames(
        Jump,
        "res/textures/Player/Tilemap/Jump/spritesheetJump.png",
        spriteFramesPerTypeOfAnimationPlayer[Jump],
        frameWidth,
        frameHeight
    );
    
    animSequencerPlayer.loadAnimationFrames(
        Attack,
        "res/textures/Player/Tilemap/Attack/spritesheetAttack.png",
        spriteFramesPerTypeOfAnimationPlayer[Attack],
        frameWidth,
        frameHeight
    );

    animSequencerPlayer.loadAnimationFrames(
        Fall,
        "res/textures/Player/Tilemap/Fall/spritesheetFall.png",
        spriteFramesPerTypeOfAnimationPlayer[Fall],
        frameWidth,
        frameHeight
    );
    
    animSequencerPlayer.loadAnimationFrames(
        Die,
        "res/textures/Player/Tilemap/Die/spritesheetDie.png",
        spriteFramesPerTypeOfAnimationPlayer[Die],
        frameWidth,
        frameHeight
    );

}

void Player::setPlayerPosition(sf::Vector2f incomingPosition) {
    shape.setPosition(incomingPosition);
    sf::Vector2f shapeSize = shape.getSize();
    sf::Vector2f collisionSize = collisionShape.getSize();

    if(isOnGround) {
        collisionShape.setPosition(
        incomingPosition.x + (shapeSize.x - collisionSize.x) / 2.0f,
        (incomingPosition.y + (shapeSize.y - collisionSize.y) / 2.0f) + 1.0f
        );
    } else {
        collisionShape.setPosition(
            incomingPosition.x + (shapeSize.x - collisionSize.x) / 2.0f,
            incomingPosition.y + (shapeSize.y - collisionSize.y) / 2.0f
        );
    }
    
    currentSpritePlayer.setPosition(incomingPosition);
}

void Player::setTexture(sf::Texture* texture) {
    sf::Vector2u textureSize = texture->getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        std::cout << "Error: Texture is empty or not loaded properly!" << std::endl;
    } else {
        shape.setTexture(texture);
    }
}

void Player::setSize(float sizeX, float sizeY) {
    shape.setSize(sf::Vector2f(sizeX, sizeY));
}

void Player::handleMovement(float deltaTime) {

    velocity.y += gravity * deltaTime;

    if (movingLeft) {
        velocity.x = -speed;
        currentAction = Run;
        isMoving = true;
        std::cout << "Player is moving left. currentAction: " << currentAction << std::endl;
    } else if (movingRight) {
        velocity.x = speed;
        currentAction = Run;
        isMoving = true;
        std::cout << "Player is moving right. currentAction: " << currentAction << std::endl;
    }

    shape.move(velocity * deltaTime);
    currentSpritePlayer.setPosition(shape.getPosition());
}

void Player::updateAnimation(float deltaTime) {
    if (animationClockPlayer.getElapsedTime().asSeconds() >= animationInterval) {
        animationClockPlayer.restart();
        
        int totalFrames = spriteFramesPerTypeOfAnimationPlayer[currentAction];
        
        currentFrame = (currentFrame + 1) % totalFrames;
        
        currentSpritePlayer = animSequencerPlayer.getCurrentSpritePlayer(currentAction, currentFrame);
        
        if (onInverseDirection) {
            currentSpritePlayer.setScale(-1.f, 1.f);
            currentSpritePlayer.setOrigin(currentSpritePlayer.getLocalBounds().width, 0.f);
        } else {
            currentSpritePlayer.setScale(1.f, 1.f);
            currentSpritePlayer.setOrigin(0.f, 0.f);
        }
        
        currentSpritePlayer.setPosition(shape.getPosition());
    }
}

void Player::setCurrentAction(AnimationType newAction) {
    
    currentAction = newAction;
}

void Player::takeDamage(int damage) {

    life = life - damage;
}
