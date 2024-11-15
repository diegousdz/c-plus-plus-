#pragma once
#include "Warrior.h"
#include <SFML/Graphics.hpp>
#include "./../Core/AnimationSequencer.h"
#include <iostream>

class Orc : Warrior
{

public:
    enum AnimationType {
        Attack,
        Die,
        Hurt,
        Idle,
        Run,
    };

    Orc();

    int spriteFramesPerTypeOfAnimationOrc[5] = {7, 9, 3, 4, 6}; 
    
    sf::Sprite currentSpriteOrc;
    AnimationSequencer animSequencerOrc;
    float speed = 100.0f;
    int currentFrame = 0;
    float animationInterval = 0.1f;
    AnimationType currentAction = Idle;
    sf::Clock animationClockOrc;
    
    sf::RectangleShape shape;
    sf::RectangleShape collisionShape;
    sf::Texture textureOrc;
    sf::Vector2f velocity;

    float gravity = 300.0f;
    bool isOnGround = false;
    bool isMoving = false;
    bool onInverseDirection = false;

    bool movingLeft = false;
    bool movingRight = false;

    bool isAttacking = false;
    bool isDead = false;
    bool isHurted = false;
    bool isIdle = false;
    bool isRunning = false;

    bool animationsLoaded = false;
    
    
    // functiones from base class
    void attack(Warrior* warrior) override;
    void takeDamage(int damage);
    
    void loadAnimationsOrc();
    
};
