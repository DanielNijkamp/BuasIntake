#pragma once

#include <chrono>

#include "../../Behaviour/FixedUpdatable.h"
#include "../../Behaviour/Transformable.h"
#include "../../Collision/Screenbounds.h"
#include "../../Systems/ScrollSystem.h"

template <class T = Transformable>
class Spawner : public ScrollSystem<T>, public FixedUpdatable
{
public:
    explicit Spawner(
        const Screenbounds& screenbounds,
        bool& canScroll,
        const float& acceleration,
        const sf::Vector2f& startPos,
        const sf::Vector2f& endPos,
        const sf::Vector2f& storePos,
        const float offset,
        const int minRespawnTime,
        const int maxRespawnTime)
        : ScrollSystem<T>(canScroll, acceleration, startPos, endPos, storePos), screenbounds(screenbounds),
          spawnOffsetX(offset),
          minRespawnTime(minRespawnTime),
          maxRespawnTime(maxRespawnTime)
    {
        lastSpawnTime = 0;
    }
    
    void Update(float deltaTime) override;

    void AddInactive(std::initializer_list<std::shared_ptr<T>> objects) override {
        ScrollSystem<T>::AddInactive(objects);
    }

protected:
    void Activate() override;
    void DeActivate(std::shared_ptr<T> obj) override;

private:
    Screenbounds screenbounds;
    const float spawnOffsetX;
    const int minRespawnTime;
    const int maxRespawnTime;
    std::time_t lastSpawnTime;
};

template <class T>
void Spawner<T>::Update(float deltaTime)
{
    if (!this->canScroll) return;
    
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    if (!this->activeObjects.empty() && this->activeObjects.at(0)->position.y >= this->endPosition.y) 
    {
        auto it = this->activeObjects.begin();
        std::shared_ptr<T> temp = *it;
        this->activeObjects.erase(it);
        DeActivate(temp);
    }

    if (this->activeObjects.empty() 
       && (currentTime - lastSpawnTime) >= minRespawnTime) 
    {
        Activate();
        lastSpawnTime = currentTime;
    }

    for (auto& obj : this->activeObjects)
    {
        obj->UpdatePositions(obj->position + sf::Vector2f(0, this->acceleration * deltaTime));
    }
}

template <class T>
void Spawner<T>::Activate()
{
    auto obj = this->PopFront();
    
    if (obj != nullptr) 
    {
        float randomX = spawnOffsetX + rand() % static_cast<int>(screenbounds.width - 2 * spawnOffsetX);
        sf::Vector2f randomPosition(randomX, this->startPosition.y);

        if(this->activeObjects.empty())
        {
            obj->UpdatePositions(randomPosition);
        }
        else
        {
            auto lastObj = this->activeObjects.back();
            sf::Vector2f newPos(lastObj->position.x, lastObj->position.y - lastObj->sprite.getGlobalBounds().height);
            obj->UpdatePositions(newPos);
        }

        this->activeObjects.push_back(obj);
    }
}

template <class T>
void Spawner<T>::DeActivate(std::shared_ptr<T> obj)
{
    obj->UpdatePositions(this->storePosition);
    this->ReleaseBack(obj);
}
