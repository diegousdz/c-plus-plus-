#pragma once
#include "Player.h"

class Crown
{
public:

    Crown(const sf::Texture& texture);

    bool getCrownHasBeenTaken () const { return crownHasBeenTaken; }
    void setCrownOwnership (Player* player)
    {
        player->playerInventory.crowdIndex = 1;
        crownHasBeenTaken = true;
    }

private:
    bool crownHasBeenTaken = false;

    int shapeWidth = 32;
    float crownInitialPositionX = 3000.0f;
    float crownInitialPositionY = static_cast<float>(shapeWidth) + static_cast<float>(64);
    sf::RectangleShape  crownShape;
    sf::Texture crownTexture;
    sf::Sprite crown;

};
