#include "Orc.h"

Orc::Orc() {
    life = 1;
    health = 100.0f;
    energy = 100.0f;
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
}

void Orc::attack()
{
    if (rage >= 30) {
        std::cout << "Orc unleashes a furious attack with power: " << attackPower + 10 << std::endl;
        rage -= 30;  
    } else {
        std::cout << "Orc attacks with power: " << attackPower << std::endl;
    }
}

void Orc::takeDamage(int damage) {
    int damageTaken = damage - defense;
    if (damageTaken > 0) {
        health -= damageTaken;
        std::cout << "Orc takes " << damageTaken << " damage. Health now: " << health << std::endl;
        if (health <= 0) {
            isDead = true;
            std::cout << "The Orc has died." << std::endl;
        }
    } else {
        std::cout << "The Orc's armor absorbed the attack!" << std::endl;
    }
}

void Orc::loadAnimationsOrc()
{
    // Frame dimensions (assuming all frames are the same size)
    int frameWidth = 50;  // Adjust based on your spritesheet
    int frameHeight = 37; // Adjust based on your spritesheet

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
    
}
