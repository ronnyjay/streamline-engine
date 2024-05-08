#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

class Window
{
  public:
    Window();
    Window(const int, const int, const char *);

    void resize(const int, const int);
    void minimize(const int);
    void maximize(const int);
    void close();

    bool running() const
    {
        return !glfwWindowShouldClose(m_window);
    }

    GLFWwindow *const glfw_window_ptr() const
    {
        return m_window;
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    const char *const title() const
    {
        return m_title;
    }

    ~Window();

  private:
    GLFWwindow *m_window;

    int m_width;
    int m_height;

    const char *m_title;

    void initialize();
};

}; // namespace engine