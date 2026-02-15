#pragma once

#include "renderer/framebuffer.hpp"

#include "core/resolution.hpp"
#include "core/singleton.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

struct RenderFlags
{
    bool b_showWireframes = false;
    bool b_showCollisions = true;
};

class Renderer : public Singleton<Renderer>
{
  public:
    RenderFlags flags;

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

    void setVerticalSync(bool enable)
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

    void setResolution(Resolution &resolution)
    {
        m_framebuffer.resize(resolution.width, resolution.height);
    }

    void beginFrame();
    void endFrame();

  private:
    Framebuffer m_framebuffer;
};

} // namespace engine
