#pragma once

#include <glm/glm.hpp>

namespace engine
{

struct ForceAccumulator
{
    ForceAccumulator();

    void AddForce(const glm::vec3 &force)
    {
        AccumulatedForces += force;
    }

    glm::vec3 AccumulatedForces;
};

} // namespace engine