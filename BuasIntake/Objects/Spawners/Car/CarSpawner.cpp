#include "CarSpawner.h"

void CarSpawner::AddInactive(std::initializer_list<std::shared_ptr<Car>> objects)
{
    Spawner::AddInactive(objects);
    for (const auto& object : objects)
    {
        object->onCollisionEnter.Subscribe([&] { this->onCollision.Fire(); });
    }
}


