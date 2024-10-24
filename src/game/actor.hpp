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
    virtual void begin() {};

    /**
     * @brief
     *
     * @param dt
     */
    virtual void tick(float dt) {};

    /**
     * @brief
     *
     */
    virtual void end() {};

    /**
     * @brief
     *
     */
    virtual ~Actor()
    {
    }
};

} // namespace engine