#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

//could also be changed to have non-virtual method with sprite member.
//this assumes that every object that can be rendered is of type sprite.
//we can also use sf::RenderTarget to abstract what we should render

class Renderable
{
public:
    virtual ~Renderable() = default;
    virtual void Render(sf::RenderWindow&) = 0;
};
