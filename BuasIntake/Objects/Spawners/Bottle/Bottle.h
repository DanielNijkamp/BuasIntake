#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "../../../Behaviour/Collidable.h"
#include "../../../Behaviour/Renderable.h"
#include "../../../Behaviour/Transformable.h"

class Bottle final : public Renderable, public Collidable, public Transformable
{
public:
    explicit Bottle(sf::Vector2f targetPosition, const sf::Sprite& sprite)
        : sprite(sprite)
    {
        this->sprite.setScale(0.25f, 0.25f);
        Bottle::UpdatePositions(targetPosition);
        const auto bounds = this->sprite.getGlobalBounds();
        this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        aabb.size = bounds.getSize();

        this->isTrigger = true;
    }
    
    void Render(sf::RenderWindow& window) override;
    void UpdatePositions(sf::Vector2f position) override;
    void UpdateCollision() override;
    
    sf::Sprite sprite;
};
