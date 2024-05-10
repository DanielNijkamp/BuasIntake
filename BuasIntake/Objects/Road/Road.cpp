#include "Road.h"

void Road::Render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Road::UpdatePositions(sf::Vector2f position)
{
    this->position = position;
    sprite.setPosition(this->position);
}
