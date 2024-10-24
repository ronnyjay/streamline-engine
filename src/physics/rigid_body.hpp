#pragma once

#include "math/transform.hpp"

namespace engine
{

struct RigidBody
{
    RigidBody()
    {
    }

    Transform transform;
};

} // namespace engine