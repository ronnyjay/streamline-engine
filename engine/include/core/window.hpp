#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "assert.hpp"    // IWYU pragma: keep
#include "event.hpp"     // IWYU pragma: keep
#include "setup.hpp"     // IWYU pragma: keep
#include "singleton.hpp" // IWYU pragma: keep

#include "math/vec2.hpp" // IWYU pragma: keep

namespace engine
{

enum class WindowMode
{
    Windowed,
    Fullscreen,
    WindowedFullscreen
};

class Window
{
    struct WindowFlags
    {
        bool mouseEntered = true;
        bool mouseVisible = true;
    };

    GLFWwindow *m_glfwWindow;

    ivec2 m_lastSize;
    ivec2 m_lastPos;

    WindowMode  m_windowMode;
    WindowFlags m_windowFlags;

    EventCallback m_eventCallback;

  public:
    /**
     * @brief
     *
     * @param width
     * @param height
     * @param title
     */
    Window(int width, int height, const char *title);

    /**
     * @brief
     *
     */
    ~Window()
    {
        if (m_glfwWindow)
            glfwDestroyWindow(m_glfwWindow);

        glfwTerminate();
    }

    Window(Window const &) = delete;
    Window(Window const &&) = delete;

    Window operator=(Window const &) = delete;
    Window operator=(Window const &&) = delete;

    /**
     * @brief
     *
     * @return GLFWwindow *
     */
    operator GLFWwindow *()
    {
        return m_glfwWindow;
    }

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool isOpen() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool isVisible() const;

    /**
     * @brief
     *
     */
    void show();

    /**
     * @brief
     *
     */
    void hide();

    /**
     * @brief
     *
     */
    void swapBuffers();

    /**
     * @brief
     *
     */
    void pollEvents();

    /**
     * @brief
     *
     */
    void toggleCursor();

    /**
     * @brief
     *
     * @return ivec2
     */
    const ivec2 &getPositionInScreen() const;

    /**
     * @brief
     *
     * @return ivec2
     */
    const ivec2 &getSizeInScreen() const;

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void moveTo(int x, int y);

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void resize(int x, int y);

    /**
     * @brief
     *
     * @param mode
     */
    void setWindowMode(WindowMode mode);

    /**
     * @brief
     *
     * @tparam T
     * @param instance
     * @param fn
     */
    template <typename T>
    void setEventCallback(T *instance, void (T::*fn)(event &&e))
    {
        m_eventCallback = [instance, fn](event &&event) { (instance->*fn)(std::move(event)); };
    }

  private:
    static void framebufferCallback(GLFWwindow *window, int width, int height);

    static void maximizeCallback(GLFWwindow *window, int maximize);
    static void minimizeCallback(GLFWwindow *window, int minimize);

    static void cursorCallback(GLFWwindow *window, double x, double y);
    static void scrollCallback(GLFWwindow *window, double x, double y);

    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

} // namespace engine
