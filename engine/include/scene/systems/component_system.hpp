#pragma once

namespace engine
{

struct scene;

struct component_system
{
    virtual ~component_system() = default;

    component_system(scene *const scene)
        : m_scene(scene)
    {
    }

    virtual void update([[maybe_unused]] double dt) = 0;

  protected:
    scene *const m_scene;
};

} // namespace engine
