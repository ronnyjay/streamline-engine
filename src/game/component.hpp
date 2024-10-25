#pragma once

#include "math/transform.hpp"

namespace engine
{

struct Component
{
    /**
     * @brief Default constructor
     *
     */
    Component()
    {
    }

    Transform transform;

    /**
     * @brief Default destructor
     *
     */
    virtual ~Component()
    {
    }
};

struct PlayerInputComponent : Component
{
    PlayerInputComponent()
    {
    }
};

} // namespace engine