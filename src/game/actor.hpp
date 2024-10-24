#pragma once

#include "math/transform.hpp"

namespace engine
{

struct Actor
{
    /**
     * @brief
     *
     */
    Actor()
    {
    }

    STransform transform;

    /**
     * @brief
     *
     */
    virtual ~Actor()
    {
    }
};

} // namespace engine