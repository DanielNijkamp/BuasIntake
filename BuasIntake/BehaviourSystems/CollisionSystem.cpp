#include "CollisionSystem.h"


/* Collision handling:
 * Because our game is player-centric we only need to check if the player is colliding with something else
 * We also disable checking the collision if an object is offscreen.
 * Currently, this method is checking if any onscreen object is colliding with the player.
 *
 * Our Collidable can also be of 2 types. a normal collider or be registered as a trigger
 * If it's a trigger then we don't need to resolve collision else we do.
 * With both we also call the appropriate events, so we can loosely couple logic on collision.
 */

void CollisionSystem::CheckCollision() const
{
    sf::Vector2f movement = player->aabb.position - player->prevPosition;
    sf::Vector2f movementNormal = movement / std::sqrt(movement.x*movement.x + movement.y*movement.y);
    float maxLength = std::sqrt(movement.x*movement.x + movement.y*movement.y); 
    for (float t = 0.0f; t <= maxLength; t += collisionStep)
    {
        sf::Vector2f pointOnPath = player->prevPosition + movementNormal * t;
        player->aabb.position = pointOnPath;

        for (const auto& collidable : collidables)
        {
            if (!IsInsideScreen(collidable)) 
            {
                continue;
            }

            if (player->aabb.Overlaps(collidable->aabb)) 
            {
                if (collidable->isTrigger)
                {
                    collidable->onTriggerEnter.Fire();
                    return;
                }
                collidable->onCollisionEnter.Fire();
                ResolveOverlap(collidable);
                return;
            }
        }
    }
}

/* A derived class implementing Collidable might have logic where it might update on the screen its position.
 * If this happens we also need to update the AABB's position and if needed the size.
 */

void CollisionSystem::UpdateCollisions() const
{
    player->prevPosition = player->aabb.position;

    player->UpdateCollision();
    for (auto& collidable : collidables) 
    {
        collidable->UpdateCollision();
    }
}

bool CollisionSystem::IsInsideScreen(const std::shared_ptr<Collidable>& collidable) const
{
    return (collidable->aabb.position.x >= 0 && collidable->aabb.position.x <= screenbounds.width
        && collidable->aabb.position.y >= 0 && collidable->aabb.position.y <= screenbounds.height);
}


/* Here again we only resolve the collision of the player.
 * We never have that 2 objects collide with each other only the player with something else.
 */

void CollisionSystem::ResolveOverlap(const std::shared_ptr<Collidable>& target) const
{
    sf::FloatRect rect1(player->aabb.position, player->aabb.size);
    sf::FloatRect rect2(target->aabb.position, target->aabb.size);

    sf::FloatRect intersection;
    if (rect1.intersects(rect2, intersection))
    {
        sf::Vector2f mtd;
        mtd.x = intersection.width  * (player->aabb.position.x < target->aabb.position.x ? -1.0f : 1.0f);

        player->aabb.position += mtd;
        player->position += mtd;
    }
}

