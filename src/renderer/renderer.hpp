#pragma once

#include "framebuffer.hpp"

namespace engine
{

class Renderer
{
  public:
    Renderer()
        : m_framebuffer(800, 600)
    {
    }

    void render(int, int);

    void on_viewport_resize(int, int);

    ~Renderer()                            = default;

    Renderer(const Renderer &)             = delete;
    Renderer(const Renderer &&)            = delete;

    Renderer &operator=(const Renderer &)  = delete;
    Renderer &operator=(const Renderer &&) = delete;

  private:
    Framebuffer m_framebuffer;
};

} // namespace engine