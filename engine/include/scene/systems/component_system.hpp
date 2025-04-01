#pragma once

namespace engine
{

struct Scene;

struct ComponentSystem
{
    virtual ~ComponentSystem() = default;

    ComponentSystem(Scene *const scene)
        : m_scene(scene)
    {
    }

    virtual void update([[maybe_unused]] double dt) = 0;

  protected:
    Scene *const m_scene;
};

} // namespace engine
