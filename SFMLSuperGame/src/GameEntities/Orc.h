#pragma once
#include "Warrior.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "./../Core/AnimationSequencer.h"

#include <iostream>

class Orc : public Warrior
{

public:
    enum AnimationType {
        Attack,
        Die,
        Hurt,
        Idle,
        Run,
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

    bool isInitialized = false;
    bool hasCollidedWithPlayer = false;

    bool animationsLoaded = false;
    
    // functiones from base class
    void attack(Warrior* warrior) override;
    void takeDamage(int damage);

    // Animation and initialization
    void loadAnimationsOrc();
    void initializeDetectionZones();
    void initializeHealthBar();
    void createEnemies();


private:
    OrcState currentState = OrcState::IDLE;
    DetectionZone detectionZone;
    HealthBar healthBar;
    float patrolDistance = 256.0f;
    sf::Vector2f spawnPoint;
    float patrolStartX = 0.0f;
    bool isActive = false;

    void updateDetectionZones();
    void handleIdleState(const Player& player);
    void handlePatrolState(const Player& player);
    void handleChaseState(const Player& player);
    void handleAttackState(const Player& player);
    void handleDyingState();
    
    bool detectPlayer(const Player& player);
    bool inAttackRange(const Player& player) const;
    
    sf::Clock idleTimer;
    sf::Clock attackTimer;
};