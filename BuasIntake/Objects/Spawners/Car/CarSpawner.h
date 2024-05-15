#pragma once

#include "Car.h"

#include "../../../Collision/Screenbounds.h"
#include "../../../Systems/Event.h"
#include "../../../Systems/ScrollSystem.h"
#include "../../Spawners/Spawner.h"

class CarSpawner final : public Spawner<Car>
{
public:
    explicit CarSpawner(
        const Screenbounds& screenbounds,
        bool& canScroll,
        const float& acceleration,
        const sf::Vector2f& startPos,
        const sf::Vector2f& endPos,
        const sf::Vector2f& storePos,
        const float offset,
        const int minRespawnTime,
        const int maxRespawnTime)
        : Spawner(
            screenbounds,
            canScroll,
            acceleration,
            startPos,
            endPos,
            storePos,
            offset,
            minRespawnTime,
            maxRespawnTime)
    {
    }

    void AddInactive(std::initializer_list<std::shared_ptr<Car>> objects) override;
    
    Event<> onCollision;
};
