#include "FixedUpdateSystem.h"

void FixedUpdateSystem::Update(float deltaTime) const
{
    for (const auto& updatable : updatables)
    {
        updatable->Update(deltaTime);
    }
}
