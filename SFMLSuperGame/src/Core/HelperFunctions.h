#pragma once
#include <SFML/Graphics/Rect.hpp>

struct AABB {
    float positionX;
    float positionY;
    float width;
    float height;
};

class HelperFunctions
{
    
public:
    bool checkCollisionAABB(const AABB& box1, const  AABB& box2);
};
