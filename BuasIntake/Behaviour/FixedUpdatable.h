#pragma once

class FixedUpdatable
{
public:
    virtual ~FixedUpdatable() = default;
    virtual void Update(float deltaTime) = 0;
};
