#pragma once

#include "component_system.hpp"

namespace engine
{

struct LightingSystem : public ComponentSystem
{
    LightingSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;
};

} // namespace engine