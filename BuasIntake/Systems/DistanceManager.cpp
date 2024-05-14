#include "DistanceManager.h"

float DistanceManager::Increment(float amount)
{
    return (totalDistance += amount);
}

float DistanceManager::GetMaxDistance() const
{
    return maxDistance;
}

void DistanceManager::CheckDistance()
{
    if (!hasFired && this->totalDistance >= maxDistance)
    {
        onEndReached.Fire();
        hasFired = true;;
    }
}
