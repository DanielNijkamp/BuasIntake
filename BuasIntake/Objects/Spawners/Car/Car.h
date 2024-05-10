#pragma once
#include <SFML/Graphics.hpp>
#include "../../../Behaviour/Collidable.h"
#include "../../../Behaviour/Renderable.h"
#include "../../../Behaviour/Transformable.h"

class Car : public Renderable , public Collidable, public Transformable
{
public:
	explicit Car(sf::Vector2f targetPosition, const sf::Sprite& sprite)
		: sprite(sprite)
	{
		Car::UpdatePositions(targetPosition);
		const auto bounds = this->sprite.getGlobalBounds().getSize();
		aabb.size = bounds;
	}
	explicit Car(const sf::Sprite& sprite)
		: sprite(sprite)
	{
		const auto bounds = sprite.getGlobalBounds().getSize();
		aabb.size = bounds;
	}

	~Car() override = default;
	
	void Render(sf::RenderWindow&) override;
	void UpdateCollision() override;
	void UpdatePositions(sf::Vector2f position) override;

	/*Making this private means making 10 different methods which the sprite also contains.
	so making this public avoid code duplication. could probably be handled better via paradigm change
	or maybe use const + mutable or something where we can use the methods but not change the sprite directly.
	*/
	
	sf::Sprite sprite;
};


