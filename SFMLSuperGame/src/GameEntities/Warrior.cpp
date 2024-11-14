#include "Warrior.h"

#include <iostream>

Warrior::Warrior(int life, int dmg)
    : health(life), damage(dmg) {
    id = nextId;         // Assign the next available ID
    nextId++;            // Move to the next character ID
    if (nextId > 'Z') {  // Wrap around if we exceed 'Z'
        nextId = 'A';
    }
}
void Warrior::Attack(Warrior* target) {
    if (target) {
        target->TakeDamage(damage);
    }
}

void Warrior::TakeDamage(int damage) {
    health -= damage;
    if (health < 0)
        health = 0; 
}

void Warrior::ShowStats() const {
    std::cout << (HasId() ? "NPC " : "Player ") 
              << (HasId() ? id : '-') << " - Health: " 
              << health << ", Damage: " << damage << "\n";
}