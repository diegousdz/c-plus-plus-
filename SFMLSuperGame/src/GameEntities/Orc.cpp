#include "Orc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <random>

void Orc::loadAnimationsOrc()
{
    // Frame dimensions (assuming all frames are the same size)
    int frameWidth = 58;  // Adjust based on your spritesheet
    int frameHeight = 42; // Adjust based on your spritesheet

    animSequencerOrc.loadAnimationFramesOrc(
        Attack,
        "res/textures/Orc/Tilemap/Attack/spritesheetAttack.png",
        spriteFramesPerTypeOfAnimationOrc[Attack],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFramesOrc(
        Die,
        "res/textures/Orc/Tilemap/Die/spritesheetDie.png",
        spriteFramesPerTypeOfAnimationOrc[Die],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFramesOrc(
        Hurt,
        "res/textures/Orc/Tilemap/Fall/spritesheetHurt.png",
        spriteFramesPerTypeOfAnimationOrc[Hurt],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFramesOrc(
        Idle,
        "res/textures/Orc/Tilemap/Idle/spritesheetIdle.png",
        spriteFramesPerTypeOfAnimationOrc[Idle],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFramesOrc(
        Run,
        "res/textures/Orc/Tilemap/Fall/spritesheetRun.png",
        spriteFramesPerTypeOfAnimationOrc[Run],
        frameWidth,
        frameHeight
    );

    animationsLoaded = true;
}

void Orc::initializeDetectionZones()
{
    // Sight range
    detectionZone.sightRange.setSize(sf::Vector2f(200.0f, 60.0f));
    detectionZone.sightRange.setFillColor(sf::Color(0, 0, 255, 64));
        
    // Attack range
    detectionZone.attackRange.setSize(sf::Vector2f(60.0f, 60.0f));
    detectionZone.attackRange.setFillColor(sf::Color(255, 0, 0, 64));
}

void Orc::initializeHealthBar()
{
    healthBar.container.setSize(sf::Vector2f(healthBar.WIDTH + 4, healthBar.HEIGHT + 4));
    healthBar.container.setFillColor(sf::Color(60, 60, 60));
        
    healthBar.bar.setSize(sf::Vector2f(healthBar.WIDTH, healthBar.HEIGHT));
    healthBar.bar.setFillColor(sf::Color(255, 0, 0));
}

void Orc::updateDetectionZones()
{
    sf::Vector2f pos = shape.getPosition();
    float offset = onInverseDirection ? -detectionZone.sightRange.getSize().x : shape.getSize().x;
        
    detectionZone.sightRange.setPosition(
        pos.x + (onInverseDirection ? -detectionZone.sightRange.getSize().x : shape.getSize().x),
        pos.y
    );
        
    detectionZone.attackRange.setPosition(
        pos.x + (onInverseDirection ? -detectionZone.attackRange.getSize().x : shape.getSize().x),
        pos.y
    );
}

Orc::Orc() : Warrior('o', 30, 130) {
    SetId('o');
    SetDamage(30);
    SetHealth(120);
    
    shape.setSize(sf::Vector2f(58.0f, 42.0f));
    shape.setPosition(100, 100);
    shape.setTexture(&textureOrc);
    collisionShape.setSize(sf::Vector2f(58.0f, 42.0f));
    collisionShape.setFillColor(sf::Color(255, 0, 0, 128));
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSpriteOrc = sf::Sprite();
    loadAnimationsOrc();
    isMoving = false;
    onInverseDirection = false;
    animationsLoaded = false;
}

void Orc::handleIdleState(const Player& player) {
    if (detectPlayer(player)) {
        currentState = OrcState::CHASING;
        return;
    }
        
    if (idleTimer.getElapsedTime().asSeconds() > 2.0f) {
        currentState = OrcState::PATROLLING;
        patrolStartX = shape.getPosition().x;
        velocity.x = speed * (onInverseDirection ? -1.0f : 1.0f);
        idleTimer.restart();
    }
}


void Orc::handlePatrolState(const Player& player) {
    if (detectPlayer(player)) {
        currentState = OrcState::CHASING;
        return;
    }

    float distanceMoved = std::abs(shape.getPosition().x - patrolStartX);
    if (distanceMoved >= patrolDistance) {
        onInverseDirection = !onInverseDirection;
        patrolStartX = shape.getPosition().x;
        velocity.x = speed * (onInverseDirection ? -1.0f : 1.0f);
    }
}

void Orc::handleChaseState(const Player& player) {
    if (!detectPlayer(player)) {
        currentState = OrcState::IDLE;
        velocity.x = 0;
        return;
    }

    if (inAttackRange(player)) {
        currentState = OrcState::ATTACKING;
        velocity.x = 0;
        return;
    }

    // Move towards player
    onInverseDirection = player.getPosition().x < shape.getPosition().x;
    velocity.x = speed * (onInverseDirection ? -1.0f : 1.0f);
}

void Orc::handleAttackState(const Player& player) {
    if (!inAttackRange(player)) {
        currentState = OrcState::CHASING;
        return;
    }

    if (attackTimer.getElapsedTime().asSeconds() > 1.0f) {
        attack(static_cast<Warrior*>(&const_cast<Player&>(player)));
        attackTimer.restart();
    }
}

void Orc::handleDyingState() {
    if (currentFrame >= spriteFramesPerTypeOfAnimationOrc[Die] - 1) {
        isActive = false;
        currentState = OrcState::INACTIVE;
        shape.setPosition(spawnPoint);
    }
}

bool Orc::detectPlayer(const Player& player) {
    return detectionZone.sightRange.getGlobalBounds().intersects(
        player.shape.getGlobalBounds()
    );
}

bool Orc::inAttackRange(const Player& player) const
{
    return detectionZone.attackRange.getGlobalBounds().intersects(
        player.shape.getGlobalBounds()
    );
}

void Orc::attack(Warrior* warrior)
{
    if (dis(gen) < 0.25) { 
        int criticalDamage = GetDamage() * 2;
        std::cout << "Orc " << "lands a critical hit!" << '\n';
        warrior->receivedDamage(criticalDamage);
    } else {
        std::cout << "Orc " << GetName() << " swing his a weapon" << '\n';
        warrior->receivedDamage(GetDamage());
    }
}

void Orc::takeDamage(int damage) {
    int damageTaken = damage;
    if (damageTaken > 0) {
        int currentHealth = GetHealth();
        SetHealth(currentHealth -= damageTaken);
       // std::cout << "Orc takes " << damageTaken << " damage. Health now: " << GetHealth << std::endl;
       // reflect change into the orc stats
        if (GetHealth() <= 0) {
            isDead = true;
           std::cout << "The Orc has died." << std::endl;
        }
    } 
}

