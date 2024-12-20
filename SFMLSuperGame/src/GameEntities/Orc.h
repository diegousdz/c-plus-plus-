﻿#pragma once
#include "Warrior.h"
#include "Player.h"
#include "./../Core/AnimationSequencer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Orc : public Warrior {
public:
    enum AnimationType {
        Attack,
        Die,
        Hurt,
        Idle,
        Run
    };

    enum class OrcState {
        IDLE,
        PATROLLING,
        CHASING,
        ATTACKING,
        DYING,
        INACTIVE
    };

    struct DetectionZone {
        sf::RectangleShape sightRange;
        sf::RectangleShape attackRange;
    };

    struct HealthBar {
        sf::RectangleShape container;
        sf::RectangleShape bar;
        const float WIDTH = 50.0f;
        const float HEIGHT = 8.0f;
        const float OFFSET_Y = -15.0f;
    };

    Orc();
    void setTexture(sf::Texture* texture);

    int spriteFramesPerTypeOfAnimationOrc[1] = {4};

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

    bool isInitialized = false;
    bool hasCollidedWithPlayer = false;
    bool animationsLoaded = false;

    void attack(Warrior* warrior) override;
    void takeDamage(int damage);
    void update(float deltaTime);
    void updateAnimation(float deltaTime);
    void loadAnimationsOrc();

private:
    OrcState currentState = OrcState::IDLE;
    DetectionZone detectionZone;
    HealthBar healthBar;
    float patrolDistance = 256.0f;
    sf::Vector2f spawnPoint;
    float patrolStartX = 0.0f;
    bool isActive = false;

    sf::Clock idleTimer;
    sf::Clock attackTimer;
};