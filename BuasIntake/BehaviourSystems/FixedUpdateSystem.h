#pragma once
#include <initializer_list>
#include <memory>
#include <vector>

#include "../Behaviour/FixedUpdatable.h"

class FixedUpdateSystem final
{
public:
    explicit FixedUpdateSystem(std::initializer_list<std::shared_ptr<FixedUpdatable>> updatables) : updatables(updatables.begin(), updatables.end()) {}
    
    void Update(float deltaTime) const;
private:
    std::vector<std::shared_ptr<FixedUpdatable>> updatables;
    
};
