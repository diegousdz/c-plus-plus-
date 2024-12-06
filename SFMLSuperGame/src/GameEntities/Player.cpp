#include "Player.h"
#include "../Core/ResourceManager.h"

Player::Player(std::string playerName, Inventory inventory) : Warrior(100, 20) {
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

Player::Player() : Warrior(100, 20) {
    name = "Kael";
    playerInventory = Inventory();
    hasKingdomCrownInInventory = false;
    life = 3;
    health = 48.0f;
    energy = 100.0f;
    isMagicBeltEquipped = false;
    shape.setSize(sf::Vector2f(50.0f, 37.0f));
    shape.setPosition(100, 100);
    shape.setTexture(&texturePlayer);
    collisionShape.setSize(sf::Vector2f(50.0f, 37.0f));
    collisionShape.setFillColor(sf::Color(255, 0, 0, 128));
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSpritePlayer = sf::Sprite();
    loadAnimationsPlayer();
    isMoving = false;
    onInverseDirection = false;
}

void Player::loadAnimationsPlayer() {
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
    currentSpritePlayer.setPosition(incomingPosition);
    sf::Vector2f collisionSize = collisionShape.getSize();
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
    if (shape.getPosition().y != previousPosition.y) {
        velocity.y += gravity * 16 * deltaTime;
        previousPosition.x = shape.getPosition().x;
    }
    
    if (movingLeft) {
        velocity.x = -speed;
        currentAction = Run;
        isMoving = true;
    } else if (movingRight) {
        velocity.x = speed;
        currentAction = Run;
        isMoving = true;
    }

    shape.move(velocity * deltaTime);
    previousPosition.y = shape.getPosition().y;
}

void Player::updateAnimation(float deltaTime) {
    if (animationClockPlayer.getElapsedTime().asSeconds() >= animationInterval) {
        animationClockPlayer.restart();

        int totalFrames = spriteFramesPerTypeOfAnimationPlayer[currentAction];
        
        if (currentAction == Jump) {
            if (!hasPlayerJump) {
                currentFrame = 0;
            } else {
                if (currentFrame < totalFrames - 1) {
                    currentFrame++;
                } else {
                    currentFrame = totalFrames - 1;
                }
            }
        } else {
            currentFrame = (currentFrame + 1) % totalFrames;
        }

        currentSpritePlayer = animSequencerPlayer.getCurrentSpritePlayer(currentAction, currentFrame);

        if (onInverseDirection) {
            currentSpritePlayer.setScale(-1.f, 1.f);
            currentSpritePlayer.setOrigin(currentSpritePlayer.getLocalBounds().width, 0.f);
        } else {
            currentSpritePlayer.setScale(1.f, 1.f);
            currentSpritePlayer.setOrigin(0.f, 0.f);
        }   

        sf::Vector2f currentShapeSize = shape.getSize();
        sf::Vector2f newShapeSize;

        switch (currentAction) {
        case Run:
            newShapeSize.x = 20.0f;
            newShapeSize.y = currentShapeSize.y;
            break;
        case Idle:
            newShapeSize.x = 23.0f;
            newShapeSize.y = currentShapeSize.y;
            break;
        case Jump:
            newShapeSize.x = 18.0f;
            newShapeSize.y = currentShapeSize.y;
            break;
        case Fall:
            newShapeSize.x = 19.0f;
            newShapeSize.y = currentShapeSize.y;
            break;
        default:
            newShapeSize = currentShapeSize;
            newShapeSize.y = currentShapeSize.y;
            break;
        }

        shape.setSize(newShapeSize);
        currentSpritePlayer.setPosition(shape.getPosition().x - 10.0f, shape.getPosition().y);
    }
}

void Player::setCurrentAction(AnimationType newAction) {
    currentAction = newAction;
}

void Player::takeDamage(int damage) {
    life = life - damage;
}

void Player::updateGroundState()
{
    wasOnGround = isOnGround; 
}
