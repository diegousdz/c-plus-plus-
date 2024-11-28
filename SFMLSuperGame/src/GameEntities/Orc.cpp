#include "Orc.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "./../Core/AnimationSequencer.h"

void Orc::loadAnimationsOrc() {
    animSequencerOrc.loadAnimationFramesOrc(
        Attack,
        "res/textures/Orc/spritesheetenemy.png",
        spriteFramesPerTypeOfAnimationOrc[1],
        32.0f,
        32.0f
    );
    animationsLoaded = true;
}

Orc::Orc() : Warrior('o', 30, 130) {
    SetId('o');
    SetDamage(30);
    SetHealth(120);
    shape.setSize(sf::Vector2f(32.0f, 32.0f));
    shape.setPosition(100, 100);
    shape.setTexture(&textureOrc);
    collisionShape.setSize(sf::Vector2f(32.0f, 32.0f));
    collisionShape.setFillColor(sf::Color(255, 0, 0, 128));
    isOnGround = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    currentSpriteOrc = sf::Sprite();
    loadAnimationsOrc();
    isMoving = false;
    onInverseDirection = false;
    animationsLoaded = false;
}

void Orc::setTexture(sf::Texture* texture) {
    sf::Vector2u textureSize = texture->getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        std::cout << "Error: Texture is empty or not loaded properly!" << std::endl;
    } else {
        shape.setTexture(texture);
    }
}

void Orc::attack(Warrior* warrior) {
    if (dis(gen) < 0.25) {
        int criticalDamage = GetDamage() * 2;
        std::cout << "Orc lands a critical hit!" << '\n';
        warrior->receivedDamage(criticalDamage);
    } else {
        std::cout << "Orc " << GetName() << " swings a weapon" << '\n';
        warrior->receivedDamage(GetDamage());
    }
}

void Orc::takeDamage(int damage) {
    int damageTaken = damage;
    if (damageTaken > 0) {
        int currentHealth = GetHealth();
        SetHealth(currentHealth -= damageTaken);
        if (GetHealth() <= 0) {
            isDead = true;
            std::cout << "The Orc has died." << std::endl;
        }
    }
}

void Orc::update(float deltaTime) {
    if (animationClockOrc.getElapsedTime().asSeconds() >= animationInterval) {
        currentFrame++;
        if (currentFrame >= spriteFramesPerTypeOfAnimationOrc[currentAction]) {
            currentFrame = 0;
        }

        if (animationsLoaded) {
            currentSpriteOrc = animSequencerOrc.animationFramesOrcs[currentAction][currentFrame];
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
}

void Orc::updateAnimation(float deltaTime) {
    if (animationClockOrc.getElapsedTime().asSeconds() >= animationInterval) {
        currentFrame++;
        if (currentFrame >= 4) {
            currentFrame = 0;
        }

        sf::IntRect frameRect(
            currentFrame * 32,
            0,
            32,
            32
        );

        currentSpriteOrc.setTextureRect(frameRect);
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
        animationClockOrc.restart();
    }
}