#pragma once

#include <glm/glm.hpp>

namespace engine
{

struct RigidBody
{
    RigidBody();
    RigidBody(const RigidBody &) = default;

    float Mass;
    float Restituion;
    float RestitutionThreshold;

    glm::vec3 Velocity;
    glm::vec3 AngularVelocity;
};

} // namespace engine