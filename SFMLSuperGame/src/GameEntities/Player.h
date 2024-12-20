#pragma once
#include <SFML/Graphics.hpp>
#include "Warrior.h"
#include "./../Core/AnimationSequencer.h"

struct Inventory {
    Inventory(int potionRedIndex = 0, int potionGreenIndex = 0, int potionBlueIndex = 0, int weaponIndex = 0, int crowdIndex = 0)
        : potionRedIndex(potionRedIndex), potionGreenIndex(potionGreenIndex), potionBlueIndex(potionBlueIndex), weaponIndex(weaponIndex), crowdIndex(crowdIndex) {}

    int potionRedIndex = 0;
    int potionGreenIndex = 0;
    int potionBlueIndex = 0;
    int weaponIndex = 0;
    int crowdIndex = 0;
};

class Player : public Warrior {
public:
    enum AnimationType {
        Idle,
        Run,
        Jump,
        Fall,
        Attack,
        Die
    };

    int spriteFramesPerTypeOfAnimationPlayer[6] = {4, 6, 4, 2, 5, 7};
    sf::Sprite currentSpritePlayer;
    AnimationSequencer animSequencerPlayer;
    float speed = 100.0f;
    int currentFrame = 0;
    float animationInterval = 0.1f;
    AnimationType currentAction = Idle;
    sf::Clock animationClockPlayer;
    std::string name;

    Player();
    Player(std::string playerName, Inventory inventory);
    void setPlayerPosition(sf::Vector2f incomingPosition);
    void loadAnimationsPlayer();
    void setCurrentAction(AnimationType newAction);

    sf::RectangleShape shape;
    sf::RectangleShape collisionShape;
    sf::Texture texturePlayer;
    sf::Vector2f velocity;

    float gravity = 300.0f;
    bool isOnGround = false;
    bool isMoving = false;
    bool onInverseDirection = false;

    int life = 3;
    float health;
    float energy;
    Inventory playerInventory;

    bool movingLeft = false;
    bool movingRight = false;
    bool isJumping = false;

    void setTexture(sf::Texture* texture);
    void setSize(float sizeX, float sizeY);
    void handleMovement(float deltaTime);
    void updateAnimation(float deltaTime);
    void takeDamage(int damage);

    sf::Vector2f previousPosition;
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(const sf::Vector2f& pos) { shape.setPosition(pos); }

    void updateGroundState();
    bool hasPlayerMoved() const {return shape.getPosition() != previousPosition; }
    void updatePreviousPosition() {previousPosition = shape.getPosition(); }
    bool wasOnGround = false;
    
    bool hasTriggeredOnGroundSound = false;

    bool hasPlayerJump = false;
    float previousMinOverlap = 0.0f;
private:
    static std::mt19937 gen;
    static std::uniform_real_distribution<> dis;

    bool isMagicBeltEquipped;
    bool hasKingdomCrownInInventory;
};