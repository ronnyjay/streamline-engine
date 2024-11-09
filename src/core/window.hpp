#pragma once

#include "event.hpp"

#include "math/vector.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

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
    static Window *create(int width, int height, const char *title);

    operator GLFWwindow *()
    {
        return m_window;
    }

    /**
     * @brief
     *
     */
    void close();

    /**
     * @brief
     *
     */
    void swap_buffers();

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_open() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_focused() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_decorated() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_floating() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_resizable() const;

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2i get_position_in_screen() const;

    /**
     * @brief
     *
     * @return Vector2f
     */
    Vector2i get_size_in_screen() const;

    /**
     * @brief
     *s
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
        m_event_callback = [instance, fn](Event &&event)
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
    GLFWwindow   *m_window;

    WindowMode    m_mode;

    Vector2i      m_last_size;
    Vector2i      m_last_position;

    EventCallback m_event_callback;

    explicit Window(GLFWwindow *window)
        : m_window(window)
    {
        glfwGetWindowPos(m_window, &m_last_position.x, &m_last_position.y);
        glfwGetWindowSize(m_window, &m_last_size.x, &m_last_size.y);
        glfwSetWindowUserPointer(m_window, this);
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