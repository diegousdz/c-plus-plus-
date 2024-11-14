#pragma once

class Warrior
{
public:
    Warrior(int life = 100, int damage = 20, bool isPlayer = false);
    
    bool IsAttacking = false;
    bool isDead = false;
    bool isHurt = false;
    
    int attackPower = 20;
    int defense = 10;

    int GetHealth() const { return health; }
    void SetHealth(int value) { health = value; }

    int GetDamage() const { return damage; }
    void SetDamage(int value) { damage = value; }

    virtual void Attack(Warrior* target);      
    virtual void TakeDamage(int damage);      
    virtual void ShowStats() const;
    
    bool IsAlive() const { return health > 0; }
    static int RandomInt(int min, int max);

private:
    int health;            
    int damage;            
    char id;
};
