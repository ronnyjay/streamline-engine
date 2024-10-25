#pragma once

#include "rigid_body.hpp"

#include <memory>

namespace engine
{

struct PhysicsSystem
{
    /**
     * @brief
     *
     */
    PhysicsSystem()
    {
    }

    /**
     * @brief
     *
     * @param dt
     */
    void step(float dt);

  private:
};

} // namespace engine