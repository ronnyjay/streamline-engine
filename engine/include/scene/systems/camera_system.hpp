#pragma once

#include "component_system.hpp"

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

  private:
    void updateViews();
    void updateProjections();
};

} // namespace engine