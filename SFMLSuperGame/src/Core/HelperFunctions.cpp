#include "HelperFunctions.h"

bool HelperFunctions::checkCollisionAABB(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2)
{
    // Get positions and sizes of both shapes
    float x1 = shape1.getPosition().x;
    float y1 = shape1.getPosition().y;
    float width1 = shape1.getSize().x;
    float height1 = shape1.getSize().y;

    float x2 = shape2.getPosition().x;
    float y2 = shape2.getPosition().y;
    float width2 = shape2.getSize().x;
    float height2 = shape2.getSize().y;

    // Check for overlap on both x and y axes
    bool collisionX = x1 + width1 >= x2 && x2 + width2 >= x1;
    bool collisionY = y1 + height1 >= y2 && y2 + height2 >= y1;

    return collisionX && collisionY;
}

