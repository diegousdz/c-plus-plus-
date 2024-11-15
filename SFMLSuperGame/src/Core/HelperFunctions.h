#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class HelperFunctions
{
    
public:
    static bool checkCollisionAABB(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2);
};
