#pragma once

#include "component_system.hpp"

namespace engine
{

struct LightingSystem : public component_system
{
    LightingSystem(scene *const scene)
        : component_system(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;
};

} // namespace engine