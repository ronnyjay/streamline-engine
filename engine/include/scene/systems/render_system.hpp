#pragma once

#include "component_system.hpp"

namespace engine
{

struct RenderSystem : public ComponentSystem
{
    RenderSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    void draw();

    void update([[maybe_unused]] double dt) override
    {
    }

  private:
};

} // namespace engine
