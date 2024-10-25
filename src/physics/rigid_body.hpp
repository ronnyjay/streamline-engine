#pragma once

#include "math/transform.hpp"

namespace engine
{

struct RigidBody
{
    RigidBody(float mass = 1.0f)

    {
    }

    Transform transform;
};

} // namespace engine