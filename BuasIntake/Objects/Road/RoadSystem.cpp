#include "RoadSystem.h"

void RoadSystem::Update(float deltaTime)
{
    if (!canScroll) return;
    
    if (activeObjects.size() >= 2 && activeObjects.at(0)->position.y >= endPosition.y) 
    {
        auto it = activeObjects.begin();
        std::shared_ptr<Road> temp = *it;
        activeObjects.erase(it);
        DeActivate(temp);
    }

    if (activeObjects.size() <= 1 && activeObjects.front()->position.y >= halfwayPoint.y)
    {
        Activate();
    }


    for (auto& road : activeObjects)
    {
        road->UpdatePositions(road->position + sf::Vector2f(0, acceleration * deltaTime));
    }
}

void RoadSystem::Activate()
{
    auto ptr = PopBack();
    if (ptr != nullptr) 
    {
        if(activeObjects.empty())
        {
            ptr->UpdatePositions(startPosition);
        }
        else
        {
            auto lastRoadPos = activeObjects.back();
            
            sf::Vector2f newRoadPos(lastRoadPos->position.x, lastRoadPos->position.y - lastRoadPos->sprite.getGlobalBounds().height);
            
            ptr->UpdatePositions(newRoadPos);
        }
        activeObjects.push_back(ptr);        
    }
}

void RoadSystem::DeActivate(std::shared_ptr<Road> obj)
{
    obj->UpdatePositions(storePosition);
    ReleaseBack(std::move(obj));
}
