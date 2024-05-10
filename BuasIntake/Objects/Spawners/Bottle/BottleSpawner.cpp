#include "BottleSpawner.h"
#include <random>

void BottleSpawner::AddInactive(std::initializer_list<std::shared_ptr<Bottle>> objects)
{
    Spawner::AddInactive(objects);
    for (const auto& object : objects)
    {
        object->onTriggerEnter.Subscribe([&]
        {
            std::default_random_engine generator(time(0));

            std::uniform_int_distribution<int> distribution(minStrength, maxStrength);

            strength = strength = distribution(generator);
            this->onPickUp.Fire(strength);
            
            DeActivate(object);
        });
    }
}

