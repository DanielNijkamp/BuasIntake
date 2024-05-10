#pragma once

#include "Bottle.h"
#include "../../../Systems/ScrollSystem.h"
#include "../../../Collision/Screenbounds.h"
#include "../../../Systems/Event.h"
#include "../../Spawners/Spawner.h"

class BottleSpawner final : public Spawner<Bottle>
{
public:
    explicit BottleSpawner(
        const Screenbounds& screenbounds,
        bool& canScroll,
        const float& acceleration,
        const sf::Vector2f& startPos,
        const sf::Vector2f& endPos,
        const sf::Vector2f& storePos,
        const float offset,
        const int minRespawnTime,
        const int maxRespawnTime,
        const int minStrength,
        const int maxStrength)
        : Spawner(
            screenbounds,
            canScroll,
            acceleration,
            startPos,
            endPos,
            storePos,
            offset,
            minRespawnTime,
            maxRespawnTime),
    minStrength(minStrength),
    maxStrength(maxStrength) {}
    
    void AddInactive(std::initializer_list<std::shared_ptr<Bottle>> objects) override;

    Event<float> onPickUp;
    float strength;
    
    const int minStrength;
    const int maxStrength;
};

