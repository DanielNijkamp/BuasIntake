#include "Bottle.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Bottle::Render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Bottle::UpdateCollision()
{
    const sf::FloatRect bounds = sprite.getGlobalBounds();
    this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    aabb.position = sf::Vector2f(bounds.left, bounds.top);
}

void Bottle::UpdatePositions(const sf::Vector2f position)
{
    this->position = position;
    sprite.setPosition(this->position);
}

