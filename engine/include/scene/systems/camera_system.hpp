#pragma once

#include "component_system.hpp"
#include <cstdint>

namespace engine
{

struct Camera;

struct CameraSystem : public component_system
{
    CameraSystem(scene *const scene)
        : component_system(scene)
    {
    }

    void update([[maybe_unused]] double dt) override;

    void updateAspectRatios(uint32_t width, uint32_t height);

  private:
    void updateViews();
    void updateProjections();
};

} // namespace engine