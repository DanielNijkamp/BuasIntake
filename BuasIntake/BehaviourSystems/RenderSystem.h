#pragma once
#include <initializer_list>
#include <memory>
#include <vector>
#include "../Behaviour/Renderable.h"

class RenderSystem final
{
public:
    explicit RenderSystem(std::initializer_list<std::shared_ptr<Renderable>> renderables)
    : renderables(renderables.begin(), renderables.end()) {};
    
    void Render(sf::RenderWindow& window) const;
private:
    std::vector<std::shared_ptr<Renderable>> renderables;
};
