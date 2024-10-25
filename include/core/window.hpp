#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "event.hpp"      // IWYU pragma: keep
#include "events.hpp"     // IWYU pragma: keep
#include "monitor.hpp"    // IWYU pragma: keep
#include "resolution.hpp" // IWYU pragma: keep

namespace engine
{

class Window : public EventDispatcher
{
  public:
    Window(int width = 800, int height = 600, const char *title = "");

    operator GLFWwindow *()
    {
        return mWindow;
    }

    bool bFirstMouse   = true;
    bool bShowMouse    = false;
    bool bCaptureMouse = false;

    ~Window() {};

    Window(const Window &)  = delete;
    Window(const Window &&) = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow *mWindow;

    int         mWidth;
    int         mHeight;

    static void FramebufferSizeCallback(GLFWwindow *, int, int);

    static void WindowMinimizeCallback(GLFWwindow *, int);
    static void WindowMaximizeCallback(GLFWwindow *, int);

    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void MouseCallback(GLFWwindow *, int, int, int);

    static void ScrollCallback(GLFWwindow *, double, double);
    static void CursorPosCallback(GLFWwindow *, double, double);
};

} // namespace engine