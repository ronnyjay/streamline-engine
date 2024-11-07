#pragma once

#include "event.hpp"

#include "math/vector.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <memory>

namespace engine
{

// clang-format off
enum class WindowMode : int
{
    Fullscreen, Windowed, Borderless
};
// clang-format on

class Window
{
  public:
    static std::unique_ptr<Window> create(int width, int height, const char *title);

    operator GLFWwindow *()
    {
        return mBaseWindow;
    }

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2<int> GetPositionInScreen() const;

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2<int> GetSizeInScreen() const;

    /**
     * @brief
     *s
     * @param x
     * @param y
     */
    void Resize(int x, int y);

    /**
     * @brief
     *
     * @param w
     * @param h
     */
    void MoveTo(int w, int h);

    /**
     * @brief
     *
     * @param mode
     */
    void SetWindowMode(WindowMode mode);

    /**
     * @brief
     *
     * @param instance
     * @param fn
     */
    template <typename T>
    void SetEventCallback(T *instance, void (T::*fn)(Event &&))
    {
        mEventCallback = std::bind(fn, instance, std::placeholders::_1);
    }

    ~Window();

    Window(const Window &other)            = delete;
    Window(const Window &&other)           = delete;

    Window operator=(const Window &other)  = delete;
    Window operator=(const Window &&other) = delete;

  private:
    GLFWwindow   *mBaseWindow;

    WindowMode    mWindowMode;

    Vector2<int>  mLastSize;
    Vector2<int>  mLastPosition;

    EventCallback mEventCallback;

    explicit Window(GLFWwindow *window)
        : mBaseWindow(window)
    {
        glfwGetWindowPos(mBaseWindow, &mLastPosition.x, &mLastPosition.y);
        glfwGetWindowSize(mBaseWindow, &mLastSize.x, &mLastSize.y);
        glfwSetWindowUserPointer(mBaseWindow, this);
    }

    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

    static void MaximizeCallback(GLFWwindow *window, int maximize);
    static void MinimizeCallback(GLFWwindow *window, int minimize);

    static void ScrollCallback(GLFWwindow *window, double x, double y);
    static void CursorPosCallback(GLFWwindow *window, double x, double y);

    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

}; // namespace engine