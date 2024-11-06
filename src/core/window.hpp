#pragma once

#include "event.hpp"

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
        return m_window;
    }

    /**
     * @brief
     *
     * @return int
     */
    int x() const;

    /**
     * @brief
     *
     * @return int
     */
    int y() const;

    /**
     * @brief
     *
     * @return int
     */
    int width() const;

    /**
     * @brief
     *
     * @return int
     */
    int height() const;

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
     * @param w
     * @param h
     */
    void move_to(int w, int h);

    /**
     * @brief
     *
     * @param mode
     */
    void set_window_mode(WindowMode mode);

    /**
     * @brief
     *
     * @param instance
     * @param fn
     */
    template <typename T>
    void set_event_callback(T *instance, void (T::*fn)(Event &&))
    {
        m_event_callback = std::bind(fn, instance, std::placeholders::_1);
    }

    ~Window();

    Window(const Window &other)            = delete;
    Window(const Window &&other)           = delete;

    Window operator=(const Window &other)  = delete;
    Window operator=(const Window &&other) = delete;

  private:
    GLFWwindow   *m_window;

    int           m_x;
    int           m_y;
    int           m_width;
    int           m_height;

    EventCallback m_event_callback;

    explicit Window(GLFWwindow *window)
        : m_window(window)
    {
        glfwSetWindowUserPointer(m_window, this);

        glfwGetWindowPos(m_window, &m_x, &m_y);
        glfwGetWindowSize(m_window, &m_width, &m_height);
    }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void window_maximize_callback(GLFWwindow *window, int maximize);
    static void window_minimize_callback(GLFWwindow *window, int minimize);

    static void scroll_callback(GLFWwindow *window, double x, double y);
    static void cursor_pos_callback(GLFWwindow *window, double x, double y);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

}; // namespace engine