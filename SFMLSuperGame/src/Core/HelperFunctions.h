#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class HelperFunctions
{
public:
    static bool checkCollisionAABB(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2);
    float recalculateYPosition(int row);
    float recalculateYPositionNegate(int row);
};
