#include "Warrior.h"
#include <iostream>

// ----------------------------------------- constructors
Warrior::Warrior()
{
    health = 100;
    damage = 20;
}

Warrior::Warrior(int health, int damage)
{
    this->health = health;
    this->damage = damage;
}

Warrior::Warrior(char id)
{
    this->id = id;
    this->damage = 20;
    this->health = 100;
}

Warrior::Warrior(char id, int damage)
{
    this->id = id;
    this->damage = damage;
    this->health = 100;
}

Warrior::Warrior(char id, int damage, int health)
{
    this->id = id;
    this->damage = damage;
    this->health = health;
}

// ----------------------------------------- functions
void Warrior::Attack(Warrior* warrior) {
    if (warrior) {
        warrior->ReceivedDamage(damage);
    }
}

void Warrior::ReceivedDamage()
{
    health -= 10;
}

void Warrior::ReceivedDamage(int damageFromWarrior) {
    health -= damageFromWarrior;
    if (health < 0)
        health = 0; 
}
