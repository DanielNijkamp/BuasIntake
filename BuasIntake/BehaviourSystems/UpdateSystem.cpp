#include "UpdateSystem.h"

void UpdateSystem::Update() const
{
    for (auto& updatable : updatables)
    {
        updatable->Update();
    }
}
