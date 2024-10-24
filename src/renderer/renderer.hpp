#pragma once

#include "framebuffer.hpp"

#include "core/debug.hpp"

#include "scene/scene.hpp"

namespace engine
{

class Renderer : public Debuggable
{
  public:
    Renderer()
        : m_framebuffer(800, 600)
    {
    }

    void render(int, int);
    void render(Scene *scene, int, int);

    void on_viewport_resize(int, int);

    DEBUGGABLE()

    ~Renderer()                            = default;

    Renderer(const Renderer &)             = delete;
    Renderer(const Renderer &&)            = delete;

    Renderer &operator=(const Renderer &)  = delete;
    Renderer &operator=(const Renderer &&) = delete;

  private:
    Framebuffer m_framebuffer;
};

} // namespace engine