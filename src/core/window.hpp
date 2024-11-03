#pragma once

#include "monitor.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <memory>

namespace engine
{

class Window
{
  public:
    static std::unique_ptr<Window> Create(int width, int height, const char *title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

    operator GLFWwindow *()
    {
        return mWindow;
    }

    void SetWindowPosition(int, int);
    void SetWindowSize(int, int);

    void SetFullscreen();
    void SetWindowed();
    void SetBorderless();

    void SetMonitor(const Monitor &);

    int GetX() const
    {
        return mX;
    }

    int GetY() const
    {
        return mY;
    }

    int GetWidth() const
    {
        return mWidth;
    }

    int GetHeight() const
    {
        return mHeight;
    }

    ~Window();

    Window(const Window &other) = delete;
    Window(const Window &&other) = delete;

    Window operator=(const Window &other) = delete;
    Window operator=(const Window &&other) = delete;

  private:
    GLFWwindow *mWindow;

    int mX;
    int mY;

    int mWidth;
    int mHeight;

    GLFWmonitor *mPreferredMonitor;

    Window(int width, int height, const char *title);

    GLFWmonitor *GetMonitor()
    {
        int windowX, windowY;
        glfwGetWindowPos(mWindow, &windowX, &windowY);

        int count;
        GLFWmonitor **monitors = glfwGetMonitors(&count);

        for (int i = 0; i < count; i++)
        {
            GLFWmonitor *monitor = monitors[i];

            int monitorX, monitorY;
            int monitorWidth, monitorHeight;
            glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

            bool overlapX = windowX >= monitorX && windowX < monitorX + monitorWidth;
            bool overlapY = windowY >= monitorY && windowY < monitorY + monitorHeight;

            if (overlapX && overlapY)
            {
                return monitor;
            }
        }

        return glfwGetPrimaryMonitor();
    }
};

}; // namespace engine