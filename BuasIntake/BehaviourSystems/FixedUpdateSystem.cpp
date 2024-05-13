#include "FixedUpdateSystem.h"

void FixedUpdateSystem::Update(float deltaTime) const
{
    for (const auto& updatable : updatables)
    {
        if (updatable->canUpdate)
        {
            updatable->Update(deltaTime);
        }
    }
}
