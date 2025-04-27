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

class Window : public Singleton<Window>
{
    struct WindowFlags
    {
        bool b_mouseEntered = true;
        bool b_mouseVisible = true;
    };

    GLFWwindow   *m_glfwWindow;

    WindowMode    m_windowMode;
    EventCallback m_eventCallback;

  public:
    Window(int width, int height, const char *title);

    ~Window()
    {
        if (m_glfwWindow)
            glfwDestroyWindow(m_glfwWindow);

        glfwTerminate();
    }

    WindowFlags flags;

    Window(Window const &)            = delete;
    Window(Window const &&)           = delete;

    Window operator=(Window const &)  = delete;
    Window operator=(Window const &&) = delete;

    operator GLFWwindow *()
    {
        return m_glfwWindow;
    }

    bool                 isVisible() const;
    bool                 isOpen() const;

    void                 show();
    void                 hide();

    void                 close();

    void                 showCursor();
    void                 hideCursor();

    void                 pollEvents();
    void                 swapBuffers();

    std::tuple<int, int> getPositionInScreen() const;
    std::tuple<int, int> getSizeInScreen() const;

    void                 moveTo(int x, int y);
    void                 resize(int x, int y);

    WindowMode           getWindowMode() const;
    void                 setWindowMode(WindowMode mode);

    template <typename T>
    void setEventCallback(T *instance, void (T::*fn)(Event &&e))
    {
        m_eventCallback = [instance, fn](Event &&event) { (instance->*fn)(std::move(event)); };
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
