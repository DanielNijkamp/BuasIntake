#pragma once

#include "../Collision/AABB.h"
#include "../Systems/Event.h"

class Collidable 
{
public:
    Collidable() = default;
    virtual ~Collidable() = default;
    
    virtual void UpdateCollision() = 0;
    
    Event<> onCollisionEnter;
    Event<> onTriggerEnter;

    bool isTrigger = false;
    AABB aabb;
};
