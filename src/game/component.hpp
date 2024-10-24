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

    STransform transform;

    /**
     * @brief Default destructor
     *
     */
    virtual ~Component()
    {
    }
};

} // namespace engine