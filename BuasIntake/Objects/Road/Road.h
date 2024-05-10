#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "../../Behaviour/Renderable.h"
#include "../../Behaviour/Transformable.h"

class Road final : public Renderable, public Transformable
{
public:
    explicit Road(const sf::Sprite& sprite) : sprite(std::move(sprite))
    {
        const sf::FloatRect bounds = this->sprite.getGlobalBounds();
        this->sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        this->sprite.setScale(0.75f, 1.25f);
    }
    void Render(sf::RenderWindow& window) override;
    void UpdatePositions(sf::Vector2f position) override;
    
    sf::Sprite sprite;
};
