#pragma once

#include "math/vec3.hpp"

namespace engine
{

struct RigidBody
{
    float mass           = 1.0f;
    vec3  linearVelocity = vec3(0.0f);
};

} // namespace engine