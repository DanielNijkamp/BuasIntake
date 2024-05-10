#pragma once
#include <memory>

#include "../Player.h"
#include "../Collision/Screenbounds.h"
#include "../Behaviour/Collidable.h"

class CollisionSystem final
{
public:
    CollisionSystem(std::initializer_list<std::shared_ptr<Collidable>>collidables, const Screenbounds& screenbounds, const std::shared_ptr<Player> player)
    : screenbounds(screenbounds), player(player), collidables(collidables.begin(), collidables.end())
    {}
    
    void CheckCollision() const;
    void UpdateCollisions() const;
    
private:
    const float collisionStep = 0.05f;

    Screenbounds screenbounds;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Collidable>> collidables;

    bool IsInsideScreen(const std::shared_ptr<Collidable>& collidable) const;
    void ResolveOverlap(const std::shared_ptr<Collidable>& target) const;
};
