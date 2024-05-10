#pragma once
#include "Road.h"
#include "../../Behaviour/FixedUpdatable.h"
#include "../../Systems/ScrollSystem.h"

class RoadSystem final : public ScrollSystem<Road>, public FixedUpdatable
{
public:
    RoadSystem(bool& canScroll, const float& acceleration,
        const sf::Vector2f& startPos,
        const sf::Vector2f& endPos,
        const sf::Vector2f& storePos,
        const sf::Vector2f& halfwayPoint)
        : ScrollSystem(canScroll,acceleration, startPos, endPos, storePos), halfwayPoint(halfwayPoint)
    {}
    

    void Update(float deltaTime) override;

protected:
    void Activate() override;
    void DeActivate(std::shared_ptr<Road> obj) override;

private:
    const sf::Vector2f& halfwayPoint;
};
