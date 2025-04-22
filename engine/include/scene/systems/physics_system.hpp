#pragma once

#include "scene/systems/component_system.hpp"

namespace engine
{

struct PhysicsSystem : public ComponentSystem
{
    PhysicsSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    virtual void update([[maybe_unused]] double dt) override;
};

} // namespace engine