#include "RenderSystem.h"

void RenderSystem::Render(sf::RenderWindow& window) const
{
    for (const auto& renderable : renderables)
    {
        renderable->Render(window);
    }
}
