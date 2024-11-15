#include "Crown.h"

Crown::Crown(const sf::Texture& texture)
{
    this->shapeWidth = 32;
    this->crownInitialPositionX = 3000.0f;
    this->crownInitialPositionY = static_cast<float>(shapeWidth) + static_cast<float>(64);
    this->crownShape = sf::RectangleShape();
    this->crownTexture = texture;
    this->crown = sf::Sprite(this->crownTexture);
    this->crownHasBeenTaken = false;
}