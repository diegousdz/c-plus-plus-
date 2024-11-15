#include "Warrior.h"
#include <random>

// Define the static member variables
std::mt19937 Warrior::gen = std::mt19937(std::random_device{}());  // Mersenne Twister engine
std::uniform_real_distribution<> Warrior::dis = std::uniform_real_distribution<>(0.0, 1.0);  // Uniform distribution

Warrior::Warrior()
{
    this->id = 'o';
    this->health = 100;
    this->damage = 20;
}
Warrior::Warrior(char id, int damage, int health)
{
    this->id = id;
    this->damage = damage;
    this->health = health;
}
// warrior type orc
Warrior::Warrior(int health, int damage)
{
    id = 'o';
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

void Warrior::attack(Warrior* warrior) {
    if (warrior) {
        warrior->receivedDamage(damage);
    }
}

void Warrior::receivedDamage()
{
    health -= 10;
}

void Warrior::receivedDamage(int damageFromWarrior) {
    health -= damageFromWarrior;
    if (health < 0)
        health = 0; 
}
