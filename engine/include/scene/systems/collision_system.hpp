#pragma once

#include "scene/systems/component_system.hpp"

namespace engine
{

struct CollisionSystem : public ComponentSystem
{
    CollisionSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    virtual void update([[maybe_unused]] double dt) override;
};

} // namespace engine