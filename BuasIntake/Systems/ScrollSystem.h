#pragma once
#include <SFML/System/Vector2.hpp>
#include "Pool.h"


template <typename T>
class ScrollSystem : protected Pool<T>
{
public:
    ScrollSystem(bool& canScroll ,const float& acceleration,
                 const sf::Vector2f& startPos,
                 const sf::Vector2f& endPos,
                 const sf::Vector2f& storePos)
    : canScroll(canScroll),
      startPosition(startPos),
      endPosition(endPos),
      storePosition(storePos),
      acceleration(acceleration)
        
    {}
    
    virtual void AddActive(std::initializer_list<std::shared_ptr<T>> objects)
    {
        for (const auto& object : objects)
        {
            activeObjects.push_back(object);
        }
    }
    virtual void AddInactive(std::initializer_list<std::shared_ptr<T>> objects)
    {
        for (const auto& object: objects)
        {
            this->pool.push_back(object);
        }
    }

    bool& canScroll;

protected:
    virtual void Activate() = 0;
    virtual void DeActivate(std::shared_ptr<T> obj) = 0;
    
    std::deque<std::shared_ptr<T>> activeObjects;
    
    const sf::Vector2f& startPosition;
    const sf::Vector2f& endPosition;
    const sf::Vector2f& storePosition;
    
    const float& acceleration;
};

