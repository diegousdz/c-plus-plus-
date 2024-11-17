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

float HelperFunctions::recalculateYPosition(int row)
{
    if(row == 15)
    {
        return 32;
    } else if(row == 14)
    {
        return 64;
    } else if(row == 13)
    {
        return 96;
    } else if(row == 12)
    {
        return 128;
    } else if(row == 11)
    {
        return 160;
    } else if(row == 10)
    {
        return 192;
    } else if(row == 9)
    {
        return 224;
    } else if(row == 8)
    {
        return 256;
    } else if(row == 7)
    {
        return 288;
    } else if(row == 6)
    {
        return 320;
    } else if(row == 5)
    {
        return 352;
    } else if(row == 4)
    {
        return 384;
    } else if(row == 3)
    {
        return 416;
    } else if(row == 2)
    {
        return 448;
    }
    else if(row == 1)
    {
        return 480;
    } else if(row == 0)
    {
        return 512;
    } 
}

float HelperFunctions::recalculateYPositionNegate(int row)
{
    if(row == 15)
    {
        return 512;
    } else if(row == 14)
    {
        return 480;
    } else if(row == 13)
    {
        return 448;
    } else if(row == 12)
    {
        return 416;
    } else if(row == 11)
    {
        return 384;
    } else if(row == 10)
    {
        return 352;
    } else if(row == 9)
    {
        return 320;
    } else if(row == 8)
    {
        return 288;
    } else if(row == 7)
    {
        return 256;
    } else if(row == 6)
    {
        return 224;
    } else if(row == 5)
    {
        return 192;
    } else if(row == 4)
    {
        return 160;
    } else if(row == 3)
    {
        return 128;
    } else if(row == 2)
    {
        return 96;
    }
    else if(row == 1)
    {
        return 64;
    } else if(row == 0)
    {
        return 32;
    } 
}