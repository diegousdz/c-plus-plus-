#include "Orc.h"

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