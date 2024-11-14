#pragma once

class Warrior
{
public:
    Warrior();
    Warrior(int health = 100, int damage = 20);
    explicit Warrior(char type);
    Warrior(char id, int damage);
    Warrior(char id, int damage, int health);

    char GetName() const { return id; }
    void SetId(const char value) {id = value; }
    
    int GetHealth() const { return health; }
    void SetHealth(const int value) { health = value; }

    int GetDamage() const { return damage; }
    void SetDamage(int value) { damage = value; }

    virtual void Attack(Warrior* target);
    virtual void ReceivedDamage();         
    virtual void ReceivedDamage(int damage);      
    
    bool IsAlive() const { return health > 0; }

private:
    int health;            
    int damage;
    char id;
};
