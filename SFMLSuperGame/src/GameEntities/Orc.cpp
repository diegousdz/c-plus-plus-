#include "Orc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <random>

#include "./../Core/AnimationSequencer.h"


void Orc::loadAnimationsOrc()
{
    int frameWidth = 58;  
    int frameHeight = 42; 

    animSequencerOrc.loadAnimationFramesOrc(
        Attack,
        "res/textures/Orc/Attack/spritesheetAttack.png",
        spriteFramesPerTypeOfAnimationOrc[Attack],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFramesOrc(
        Die,
        "res/textures/Orc/Die/spritesheetDie.png",
        spriteFramesPerTypeOfAnimationOrc[Die],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFramesOrc(
        Hurt,
        "res/textures/Orc/Fall/spritesheetHurt.png",
        spriteFramesPerTypeOfAnimationOrc[Hurt],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFramesOrc(
        Idle,
        "res/textures/Orc/Idle/spritesheetIdle.png",
        spriteFramesPerTypeOfAnimationOrc[Idle],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFramesOrc(
        Run,
        "res/textures/Orc/Fall/spritesheetRun.png",
        spriteFramesPerTypeOfAnimationOrc[Run],
        frameWidth,
        frameHeight
    );

    animationsLoaded = true;
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
/*
void Orc::handleIdleState(const Player& player, ResourceManager& resourceManager) {
    if (detectPlayer(player)) {
        currentState = OrcState::CHASING;
        resourceManager.setOrcTypeOfAnimationLastSet(1, this); // Set to Run
        return;
    }
        
    if (idleTimer.getElapsedTime().asSeconds() > 2.0f) {
        currentState = OrcState::PATROLLING;
        patrolStartX = shape.getPosition().x;
        velocity.x = speed * (onInverseDirection ? -1.0f : 1.0f);
        resourceManager.setOrcTypeOfAnimationLastSet(1, this); // Set to Run
        idleTimer.restart();
    } else {
        resourceManager.setOrcTypeOfAnimationLastSet(0, this); // Set to Idle
    }
}
*/
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

void Orc::update(float deltaTime) {
//    updateDetectionZones();
    
    // Update animation frame based on time
    if (animationClockOrc.getElapsedTime().asSeconds() >= animationInterval) {
        currentFrame++;
        if (currentFrame >= spriteFramesPerTypeOfAnimationOrc[currentAction]) {
            currentFrame = 0;
        }
        
        // Get the current sprite frame from the AnimationSequencer
        if (animationsLoaded) {
            currentSpriteOrc = animSequencerOrc.animationFramesOrcs[currentAction][currentFrame];
            
            // Update sprite position and direction
            currentSpriteOrc.setPosition(shape.getPosition());
            if (onInverseDirection) {
                currentSpriteOrc.setScale(-1.0f, 1.0f);
                currentSpriteOrc.setPosition(
                    shape.getPosition().x + shape.getSize().x,
                    shape.getPosition().y
                );
            } else {
                currentSpriteOrc.setScale(1.0f, 1.0f);
            }
        }
        
        animationClockOrc.restart();
    }

    switch (currentState) {
    case OrcState::IDLE:
        currentAction = Idle;
        break;
            
    case OrcState::PATROLLING:
        currentAction = Run;

        break;
            
    case OrcState::CHASING:
        currentAction = Run;

        break;
            
    case OrcState::ATTACKING:
        currentAction = Attack;

        break;
            
    case OrcState::DYING:
        currentAction = Die;
        break;
    default: currentAction = Idle;
        break;;
    }

}