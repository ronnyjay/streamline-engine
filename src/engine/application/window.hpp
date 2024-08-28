#pragma once

#include <functional>

#include <libstreamline/debug/logger.hpp>
#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>

#include "engine/event/key_event.hpp"    // IWYU pragma: keep
#include "engine/event/mouse_event.hpp"  // IWYU pragma: keep
#include "engine/event/window_event.hpp" // IWYU pragma: keep

#include "monitor.hpp"
#include "resolution.hpp"
#include "window_config.hpp"

#define GLFW_INCLUDE_NONE
#include <engine/glfw3.h>
#include <glad/gl.h>

class window
{
  public:
    window()
        : m_logger("window")
    {
        // initialize glfw
        if (!glfwInit())
        {
            m_logger.err("failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // initialize window
        m_window = glfwCreateWindow(1280, 720, "Streamline Engine", NULL, NULL);

        if (!m_window)
        {
            m_logger.err("failed to initialize window");
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            m_logger.err("failed to initialize glad");
        }
    }

    template <typename T> void on_event(event_type t, std::function<void(T &)> fn)
    {
        m_events[t] = [fn](event &e) { fn(static_cast<T &>(e)); };
    }

    void initialize(const window_config &cfg);

    void set_monitor(monitor *);
    void set_resolution(const resolution &);
    void set_display_mode(const display_mode_e &);

    // post init
    void refresh();

    inline GLFWwindow *const glfw_window()
    {
        return m_window;
    }

    int x()
    {
        return m_x;
    }

    int y()
    {
        return m_y;
    }

    int width()
    {
        return m_config.width;
    }

    int height()
    {
        return m_config.height;
    }

    int display_mode()
    {
        return m_config.display_mode;
    }

    monitor *const primary_monitor() const
    {
        return m_primary_monitor;
    }

    monitor *const current_monitor() const
    {
        return m_current_monitor;
    }

    bool is_vsync_enabled() const
    {
        return m_config.vsync;
    }

  private:
    GLFWwindow *m_window;
    window_config m_config;

    int m_x;
    int m_y;

    int m_last_width;
    int m_last_height;
    int m_last_display_mode;

    monitor *m_primary_monitor;
    monitor *m_current_monitor;

    std::vector<monitor *> m_monitors;

    std::unordered_map<event_type, std::function<void(event &)>> m_events;

    logger m_logger;

    void load_monitors();

    void detect_primary_monitor();
    void detect_current_monitor();

    void dispatch_event(event_type, event &&);

    /**
     * @brief GLFW callback for keyboard input
     * @details Handles key logic, emits key event
     * @param window The GLFWwindow pointer
     * @param key The key's integer value
     * @param scancode The key's scancode
     * @param action (pressed, released, repeat)
     * @param mods The modifier keys
     */
    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    /**
     * @brief GLFW callback on window iconify
     * @details Handles minimize logic, emits minimize event
     * @param window The GLFWwindow pointer
     * @param minimize The state of the window (minimized, restored)
     */
    static void minimize_callback(GLFWwindow *, int);

    /**
     * @brief GLFW callback on window maximize
     * @details Handles maximize logic, emits maximize event
     * @param window The GLFWwindow pointer
     * @param maximize The state of the window (maximized, restored)
     */
    static void maximize_callback(GLFWwindow *, int);

    /**
     * @brief GLFW callback on window resize
     * @details Handles viewport logic, emits resize event
     * @param window The GLFWwindow pointer
     * @param width The width of the window (in px)
     * @param height The height of the window (in px)
     */
    static void framebuffer_size_callback(GLFWwindow *, int, int);

    static void mouse_press_callback(GLFWwindow *, int, int, int);

    static void mouse_pos_callback(GLFWwindow *, double, double);
};
