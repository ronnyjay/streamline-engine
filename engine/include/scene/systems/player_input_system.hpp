#pragma once

#include "component_system.hpp"

namespace engine
{

struct PlayerInputSystem : public component_system
{
    PlayerInputSystem(scene *const scene)
        : component_system(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;

  private:
    void updatePlayerControllers([[maybe_unused]] double dt);
    void updateCameraControllers([[maybe_unused]] double dt);
};

} // namespace engine
