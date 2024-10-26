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

enum class DisplayMode
{
    Windowed,
    Fullscreen,
    FullscreenBorderless
};

/**
 * @brief Wrapper for a GLFWwindow
 *
 */
class Window : public EventDispatcher
{
  public:
    Window(int width, int height, const char *title);

    const bool &bFirstMouse   = mFirstMouse;
    const bool &bShowMouse    = mShowMouse;
    const bool &bCaptureMouse = mCaptureMouse;

    const bool &bDecorated    = mDecorated;
    const bool &bFloating     = mFloating;
    const bool &bResizable    = mResizable;

    operator GLFWwindow *()
    {
        return mWindow;
    }

    /**
     * @brief
     *
     * @return
     */
    bool IsRunning() const;

    /**
     * @brief
     *
     */
    void SwapBuffers();

    /**
     * @brief
     *
     * @param value
     */
    void ShowMouse(bool value);

    /**
     * @brief
     *
     * @param value
     */
    void CaptureMouse(bool value);

    /**
     * @brief
     *
     * @param value
     */
    void SetDecorated(bool value);

    /**
     * @brief
     *
     * @param value
     */
    void SetFloating(bool value);

    /**
     * @brief
     *
     * @param value
     */
    void SetResizable(bool value);

    /**
     * @brief
     *
     * @param width
     * @param height
     * @param title
     * @return Window*
     */
    static Window *Create(int width, int height, const char *title);

    ~Window() {};

    Window(const Window &)            = delete;
    Window(const Window &&)           = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow *mWindow;

    int         mWidth;
    int         mHeight;

    bool        mFirstMouse   = true;
    bool        mShowMouse    = true;
    bool        mCaptureMouse = false;

    bool        mDecorated    = true;
    bool        mFloating     = false;
    bool        mResizable    = false;

    static void FramebufferSizeCallback(GLFWwindow *, int, int);

    static void WindowMaximizeCallback(GLFWwindow *, int);
    static void WindowMinimizeCallback(GLFWwindow *, int);

    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void MouseButtonCallback(GLFWwindow *, int, int, int);

    static void CursorPosCallback(GLFWwindow *, double, double);
    static void ScrollCallback(GLFWwindow *, double, double);
};

} // namespace engine