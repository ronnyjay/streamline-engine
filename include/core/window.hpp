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

    const bool &bFirstMouse   = mFirstMouse;
    const bool &bShowMouse    = mShowMouse;
    const bool &bCaptureMouse = mCaptureMouse;

    ~Window() {};

    Window(const Window &)  = delete;
    Window(const Window &&) = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow *mWindow;

    int         mWidth;
    int         mHeight;

    bool        mFirstMouse;
    bool        mShowMouse;
    bool        mCaptureMouse;

    static void FramebufferSizeCallback(GLFWwindow *, int, int);

    static void WindowMaximizeCallback(GLFWwindow *, int);
    static void WindowMinimizeCallback(GLFWwindow *, int);

    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void MouseButtonCallback(GLFWwindow *, int, int, int);

    static void CursorPosCallback(GLFWwindow *, double, double);
    static void ScrollCallback(GLFWwindow *, double, double);
};

} // namespace engine