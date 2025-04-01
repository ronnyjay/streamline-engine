#pragma once

#include "component_system.hpp"
#include <cstdint>

namespace engine
{

struct Camera;

struct CameraSystem : public ComponentSystem
{
    CameraSystem(Scene *const scene)
        : ComponentSystem(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;

    void updateAspectRatios(uint32_t width, uint32_t height);

  private:
    void updateViews();
    void updateProjections();
};

} // namespace engine