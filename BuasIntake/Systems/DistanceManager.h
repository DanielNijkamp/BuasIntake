#pragma once
#include "Event.h"

class DistanceManager final
{
public:
    explicit DistanceManager(float maxDistance) : maxDistance(maxDistance)
    {}
    
    float Increment(float amount);
    float GetMaxDistance() const;
    void CheckDistance();

    Event<> onEndReached;

private:
    bool hasFired = false;
    float totalDistance = 0.0f;
    const float maxDistance;
};
