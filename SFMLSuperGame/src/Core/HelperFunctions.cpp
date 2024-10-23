#include "HelperFunctions.h"

bool HelperFunctions::checkCollisionAABB(const AABB& box1, const  AABB& box2)
{
    bool collisionX = box1.positionX + box1.positionX >= box2.positionX && box2.positionX + box2.width >= box1.positionX;
    bool collisionY = box1.positionY + box2.positionY >= box2.positionY && box2.positionY + box2.height >= box1.positionY;

    return collisionX && collisionY;
}

