#pragma once

#include "event.hpp"
#include "video.hpp"

#include "math/vector.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

class Window
{
  public:
    static Window *Create(int width, int height, const char *title);

    operator GLFWwindow *()
    {
        return mWindow;
    }

    /**
     * @brief
     *
     */
    void Close();

    /**
     * @brief
     *
     */
    void SwapBuffers();

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsOpen() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsFocused() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsDecorated() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsFloating() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool IsResizable() const;

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2i GetPositionInScreen() const;

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2i GetSizeInScreen() const;

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void MoveTo(int x, int y);

    /**
     * @brief
     *
     * @param w
     * @param h
     */
    void Resize(int w, int h);

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
        mEventCallback = [instance, fn](Event &&event)
        {
            (instance->*fn)(std::move(event));
        };
    }

    ~Window();

    Window(const Window &other) = delete;
    Window(const Window &&other) = delete;

    Window operator=(const Window &other) = delete;
    Window operator=(const Window &&other) = delete;

  private:
    GLFWwindow   *mWindow;

    Vector2i      mLastPos;
    Vector2i      mLastSize;

    WindowMode    mWindowMode;

    EventCallback mEventCallback;

    explicit Window(GLFWwindow *window)
        : mWindow(window)
    {
        glfwGetWindowPos(mWindow, &mLastPos.x, &mLastPos.y);
        glfwGetWindowSize(mWindow, &mLastSize.x, &mLastSize.y);
        glfwSetWindowUserPointer(mWindow, this);
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