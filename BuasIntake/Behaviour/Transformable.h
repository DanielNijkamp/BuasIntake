#pragma once
#include <SFML/System/Vector2.hpp>

//ideally we would not want 2 positions to keep track of: collision + sprite
//this class should act as the single source of truth of positioning. other positions should use this

class Transformable
{
public:
    sf::Vector2f position;
    virtual ~Transformable() = default;
    virtual void UpdatePositions(sf::Vector2f position) = 0;
};
