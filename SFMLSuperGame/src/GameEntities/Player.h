#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

struct Inventory
{
    // bool hasInventoryEnabled = false;
    // Initialize the Inventory using the Inline constructor definition
    Inventory(int potionRedIndex = 0, int potionGreenIndex = 0, int potionBlueIndex = 0, int weaponIndex = 0, int crowdIndex = 0)
    : potionRedIndex(potionRedIndex), 
      potionGreenIndex(potionGreenIndex), 
      potionBlueIndex(potionBlueIndex), 
      weaponIndex(weaponIndex), 
      crowdIndex(crowdIndex)
    {}
    // Inventory Items
    int potionRedIndex = 0;
    int potionGreenIndex = 0;
    int potionBlueIndex = 0;
    int weaponIndex = 0;
    int crowdIndex = 0;

    // Helper Functions to Set Inventory Items 
    void setPotionRed(int potionAmount) { potionRedIndex = potionAmount; }
    void setPotionGreen(int potionAmount) { potionGreenIndex = potionAmount; }
    void setPotionBlue(int potionAmount) { potionBlueIndex = potionAmount; }
    void setWeapon(int weaponAmount) { weaponIndex = weaponAmount; }

    // we augment to 1 since we only have one item. 
    void augmentedCrowdIndex(int crownAmount) { crowdIndex = crownAmount; }   
};

class Player
{
    
public:
    
    std::string name;
    
    Player(); 
    Player(std::string playerName, Inventory inventory);

    sf::RectangleShape shape;
    sf::Sprite spritePlayer;
    sf::Texture texturePlayer;
    sf::Vector2f velocity;
    
    float speed = 100.0f;
    float gravity = 300.0f;
    bool isOnGround = false;


    // Attributes
    // Top right 
    int life;
    float health;
    float energy;
    Inventory playerInventory;

    //struct representing life cycle of player
    //Note: Structs allways have a ; at the end of the scope
    enum PlayerState { alive, recovering, hurt, dying, died };
    enum PlayerActions { idle, walking, jumping, attacking };

    void setTexture(sf::Texture* texture);
    void setSize(float sizeX,float sizeY);
    void configureSprite( sf::Texture playerTexture);

    void createPlayer(std::string incomingString, sf::Vector2f scaleVector);
    bool isMoving = false;
private:
    
    // Bottom
    // power-ups and objects in Inventory ( MagicBelt )
    bool isMagicBeltEquipped;
    bool hasKingdomCrownInInventory = false;
};

