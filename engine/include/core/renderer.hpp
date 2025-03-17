#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "core/window.hpp"
#include "renderer/framebuffer.hpp"

namespace engine
{

class Window;

struct scene;

class Renderer
{
  public:
    Renderer(uint32_t width, uint32_t height)
        : m_framebuffer(width, height)
    {
        glDepthFunc(GL_LESS);

        setViewport(0, 0, width, height);
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void enableVsync(bool enable)
    {
        glfwSwapInterval(static_cast<int>(enable));
    }

    void enableDepth(bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void setViewport(int x, int y, int w, int h)
    {
        glViewport(x, y, w, h);
    }

    void setClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void begin(const std::shared_ptr<scene> &s);

  private:
    Framebuffer m_framebuffer;
};

} // namespace engine