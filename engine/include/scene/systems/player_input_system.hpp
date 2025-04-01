#pragma once

#include "component_system.hpp"

namespace engine
{

struct PlayerInputSystem : public ComponentSystem
{
    PlayerInputSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;

  private:
    void updatePlayerControllers([[maybe_unused]] double dt);
    void updateCameraControllers([[maybe_unused]] double dt);
};

} // namespace engine
