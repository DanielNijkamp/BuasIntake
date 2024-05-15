#pragma once
#include <SFML/System/Vector2.hpp>

struct AABB final
{
    sf::Vector2f position; 
    sf::Vector2f size;
    
    bool Overlaps(const AABB& other) const;
};
