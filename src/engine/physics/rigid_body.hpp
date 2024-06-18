#pragma once

#include <glm/glm.hpp>

namespace engine
{

struct RigidBody
{
    RigidBody();
    RigidBody(const RigidBody &) = default;

    float Mass;
    float Restitution;
    float RestitutionThreshold;

    glm::vec3 Velocity;
    glm::vec3 Impulse;
};

} // namespace engine