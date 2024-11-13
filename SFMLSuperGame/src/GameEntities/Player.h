#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "./../Core/AnimationSequencer.h"

struct Inventory
{
    Inventory(int potionRedIndex = 0, int potionGreenIndex = 0, int potionBlueIndex = 0, int weaponIndex = 0, int crowdIndex = 0)
        : potionRedIndex(potionRedIndex), potionGreenIndex(potionGreenIndex), potionBlueIndex(potionBlueIndex), weaponIndex(weaponIndex), crowdIndex(crowdIndex)
    {}

    int potionRedIndex = 0;
    int potionGreenIndex = 0;
    int potionBlueIndex = 0;
    int weaponIndex = 0;
    int crowdIndex = 0;
};

class Player
{
public:
    enum AnimationType {
        Idle,
        Run,
        Jump,
        Fall,
        Attack,
        Die
    };

    int spriteFramesPerTypeOfAnimation[6] = {4, 6, 4, 2, 5, 7};  // Frames for each animation

    sf::Sprite currentSprite;
    AnimationSequencer animSequencer;
    float speed = 100.0f;
    int currentFrame = 0;
    float animationInterval = 0.1f;
    AnimationType currentAction = Idle;  // Default action
    sf::Clock animationClock;
    
    std::string name;

    Player();
    void setPlayerPosition(sf::Vector2f incomingPosition);
    void loadAnimations();
    Player(std::string playerName, Inventory inventory);

    sf::RectangleShape shape;
    sf::RectangleShape collisionShape;
    sf::Texture texturePlayer;
    sf::Vector2f velocity;
    
    float gravity = 300.0f;
    bool isOnGround = false; 
    bool isMoving = false;
    bool onInverseDirection = false;

    int life;
    float health;
    float energy;
    Inventory playerInventory;

    bool movingLeft = false;
    bool movingRight = false;
    bool isJumping = false;

    enum PlayerState { alive, recovering, hurt, dying, died };

    void setTexture(sf::Texture* texture);
    void setSize(float sizeX, float sizeY);
    void configureSprite(sf::Texture playerTexture);

    void handleMovement(float deltaTime);
    void updateAnimation(float deltaTime);
    
    sf::Vector2f previousPosition;
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(const sf::Vector2f& pos) { shape.setPosition(pos); }
private:
    bool isMagicBeltEquipped;
    bool hasKingdomCrownInInventory;
};
