#include "Orc.h"


void Orc::loadAnimationsOrc()
{
    // Frame dimensions (assuming all frames are the same size)
    int frameWidth = 58;  // Adjust based on your spritesheet
    int frameHeight = 42; // Adjust based on your spritesheet

    animSequencerOrc.loadAnimationFrames(
        Attack,
        "res/textures/Orc/Tilemap/Attack/spritesheetAttack.png",
        spriteFramesPerTypeOfAnimationOrc[Attack],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFrames(
        Die,
        "res/textures/Orc/Tilemap/Die/spritesheetDie.png",
        spriteFramesPerTypeOfAnimationOrc[Die],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFrames(
        Hurt,
        "res/textures/Orc/Tilemap/Fall/spritesheetHurt.png",
        spriteFramesPerTypeOfAnimationOrc[Hurt],
        frameWidth,
        frameHeight
    );
    
    animSequencerOrc.loadAnimationFrames(
        Idle,
        "res/textures/Orc/Tilemap/Idle/spritesheetIdle.png",
        spriteFramesPerTypeOfAnimationOrc[Idle],
        frameWidth,
        frameHeight
    );

    animSequencerOrc.loadAnimationFrames(
        Run,
        "res/textures/Orc/Tilemap/Fall/spritesheetRun.png",
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

