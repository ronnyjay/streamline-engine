#pragma once

#include "component_system.hpp"

namespace engine
{

struct FollowSystem : public component_system
{
    FollowSystem(scene *const scene)
        : component_system(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;
};

} // namespace engine
