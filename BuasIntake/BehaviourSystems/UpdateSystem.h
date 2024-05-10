#pragma once
#include <memory>
#include <vector>

#include "../Behaviour/Updatable.h"

class UpdateSystem final
{
public:
    explicit UpdateSystem(std::initializer_list<std::shared_ptr<Updatable>> updatables)
    : updatables(updatables.begin(), updatables.end()) {}

    void Update() const;
private:
    std::vector<std::shared_ptr<Updatable>> updatables;
};
