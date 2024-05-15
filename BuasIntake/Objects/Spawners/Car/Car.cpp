#include "Car.h"

void Car::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Car::UpdateCollision()
{
	const sf::FloatRect bounds = sprite.getGlobalBounds();
	this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	aabb.position = sf::Vector2f(bounds.left, bounds.top);
}

void Car::UpdatePositions(const sf::Vector2f position)
{
	this->position = position;
	sprite.setPosition(this->position);
}




