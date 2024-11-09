#pragma once

#include "framebuffer.hpp"

namespace engine
{

class Renderer
{
  public:
    Renderer()
        : mFramebuffer(800, 600)
    {
    }

    void Render(int, int);

    void OnViewportResize(int, int);

    ~Renderer() = default;

    Renderer(const Renderer &) = delete;
    Renderer(const Renderer &&) = delete;

    Renderer &operator=(const Renderer &) = delete;
    Renderer &operator=(const Renderer &&) = delete;

  private:
    Framebuffer mFramebuffer;
};

} // namespace engine