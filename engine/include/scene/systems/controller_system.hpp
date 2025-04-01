#pragma once

#include "component_system.hpp"

namespace engine
{

struct ControllerSystem : public ComponentSystem
{
    ControllerSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;

  private:
    void updatePlayerPositions([[maybe_unused]] double dt);
    void updatePlayerRotations([[maybe_unused]] double dt);
};

} // namespace engine