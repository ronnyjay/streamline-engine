#pragma once

#include <functional>
#include <libstreamline/debug/logger.hpp>
#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>

#include "monitor.hpp"
#include "resolution.hpp"
#include "window_config.hpp"

#include "engine/event/key_event.hpp"
#include "engine/event/mouse_event.hpp"
#include "engine/event/window_event.hpp"

#define GLFW_INCLUDE_NONE
#include <engine/glfw3.h>
#include <glad/gl.h>

class window
{
  public:
    window()
        : m_log("window")
    {
        // initialize glfw
        if (!glfwInit())
        {
            m_log.err("failed to initialize glfw");
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
            m_log.err("failed to initialize window");
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            m_log.err("failed to initialize glad");
        }
    }

    // pre init
    void on_resize(resize_event::callback);
    void on_minimize(minimize_event::callback);
    void on_maximize(maximize_event::callback);
    void on_key_press(key_press_event::callback);
    void on_mouse_move(mouse_move_event::callback);
    void on_mouse_click(mouse_click_event::callback);
    void on_mouse_scroll(mouse_scroll_event::callback);

    void initialize(const window_config &cfg);

    void set_monitor(monitor *);
    void set_resolution(const resolution &);
    void set_display_mode(const display_mode_e &);

    void set_mouse_press_callback(const std::function<void(int, int, int)> &);
    void set_mouse_pos_callback(const std::function<void(double, double)> &);

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
        return m_cfg.width;
    }

    int height()
    {
        return m_cfg.height;
    }

    int display_mode()
    {
        return m_cfg.display_mode;
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
        return m_cfg.vsync;
    }

  private:
    logger m_log;
    window_config m_cfg;
    GLFWwindow *m_window;

    int m_x;
    int m_y;

    int m_last_width;
    int m_last_height;
    int m_last_display_mode;

    monitor *m_primary_monitor;
    monitor *m_current_monitor;

    std::vector<monitor *> m_monitors;

    resize_event::callback m_on_resize;
    minimize_event::callback m_on_minimize;
    maximize_event::callback m_on_maximize;
    key_press_event::callback m_on_key_press;
    mouse_move_event::callback m_on_mouse_move;
    mouse_click_event::callback m_on_mouse_click;
    mouse_scroll_event::callback m_on_mouse_scroll;

    void load_monitors();

    void detect_primary_monitor();
    void detect_current_monitor();

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
    std::function<void(int, int, int)> m_app_mouse_press_cb;

    static void mouse_pos_callback(GLFWwindow *, double, double);
    std::function<void(double, double)> m_app_mouse_pos_cb;
};
