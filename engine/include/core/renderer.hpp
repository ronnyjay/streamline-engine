#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

class Renderer
{
  public:
    Renderer()
    {
        glDepthFunc(GL_LESS);

        setViewport(0, 0, 800, 600);
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
};

} // namespace engine