#pragma once
#include <random>
#include <SFML/Graphics.hpp>

class Warrior {
public:
    Warrior();
    Warrior(int health = 100, int damage = 20);
    explicit Warrior(char type);
    Warrior(char id, int damage);
    Warrior(char id, int damage, int health);

    char GetName() const { return id; }
    void SetId(const char value) { id = value; }

    int GetHealth() const { return health; }
    void SetHealth(const int value) { health = value; }

    int GetDamage() const { return damage; }
    void SetDamage(int value) { damage = value; }

    virtual void attack(Warrior* target);
    virtual void receivedDamage();
    virtual void receivedDamage(int damage);

    bool IsAlive() const { return health > 0; }

    static std::mt19937 gen;
    static std::uniform_real_distribution<> dis;

private:
    int health;
    int damage;
    char id;
};