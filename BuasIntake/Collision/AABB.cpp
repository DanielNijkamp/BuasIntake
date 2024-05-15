#include "AABB.h"

bool AABB::Overlaps(const AABB& other) const
{
    if (position.x < other.position.x + other.size.x && 
            position.x + size.x > other.position.x && 
            position.y < other.position.y + other.size.y && 
            position.y + size.y > other.position.y) 
    {
        return true;
    }
    return false;
}

