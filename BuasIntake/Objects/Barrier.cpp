#include "Barrier.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Barrier::Render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Barrier::Init(sf::Vector2f position, sf::Vector2f scale)
{
    sprite.setScale(scale.x, scale.y);
    sprite.setPosition(position);

    this->UpdateCollision();
}

void Barrier::UpdateCollision()
{
    const sf::FloatRect globalBounds = sprite.getGlobalBounds();
    aabb.position = sf::Vector2f(globalBounds.left, globalBounds.top);
    aabb.size = sf::Vector2f(globalBounds.width, globalBounds.height);
}
