#pragma once
#include "Warrior.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Orc : public Warrior
{
private:
   
public:

    int rage = 50;  
    int armor = 30;
    
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float gravity = 300.0f;
    bool isOnGround = false;
    float enemySize = 64;
    
    Orc() {
        health = 120;       
        attackPower = 25;   
        defense = 15;
        enemySize = 64;
        shape.setSize(sf::Vector2f(enemySize, enemySize));
        shape.setFillColor(sf::Color::Red);
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    
    void attack() override;
    
    void takeDamage(int damage);
};
