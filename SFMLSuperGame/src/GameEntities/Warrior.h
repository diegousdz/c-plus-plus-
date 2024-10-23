#pragma once

class Warrior
{
public:
    bool IsAttacking = false;
    bool isDead = false;
    bool isHurt = false;

    int health = 100;
    int attackPower = 20;
    int defense = 10;

    virtual void attack();
    
};
