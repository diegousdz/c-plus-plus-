#include "Warrior.h"
#include <random>

std::mt19937 Warrior::gen = std::mt19937(std::random_device{}());
std::uniform_real_distribution<> Warrior::dis = std::uniform_real_distribution<>(0.0, 1.0);

Warrior::Warrior() {
    id = 'o';
    health = 100;
    damage = 20;
}

Warrior::Warrior(char id, int damage, int health) {
    this->id = id;
    this->damage = damage;
    this->health = health;
}

Warrior::Warrior(int health, int damage) {
    id = 'o';
    this->health = health;
    this->damage = damage;
}

Warrior::Warrior(char id) {
    this->id = id;
    damage = 20;
    health = 100;
}

Warrior::Warrior(char id, int damage) {
    this->id = id;
    this->damage = damage;
    health = 100;
}

void Warrior::attack(Warrior* warrior) {
    if (warrior) 
        warrior->receivedDamage(damage);
}

void Warrior::receivedDamage() {
    health -= 10;
}

void Warrior::receivedDamage(int damageFromWarrior) {
    health -= damageFromWarrior;
    if (health < 0) {
        health = 0;
    }
}