#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "../Behaviour/Collidable.h"
#include "../Behaviour/Renderable.h"


class Barrier final : public Renderable, public Collidable
{
public:
    Barrier(sf::Sprite sprite, sf::Vector2f position, sf::Vector2f scale) : 
        sprite(std::move(sprite))
    {
        Init(position, scale);
    }
    ~Barrier() override = default;
    
    void Render(sf::RenderWindow&) override;
    void UpdateCollision() override;

private:
    sf::Sprite sprite;

    void Init(sf::Vector2f position, sf::Vector2f scale);
};
