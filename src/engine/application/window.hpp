#pragma once

#include <functional>
#include <libstreamline/debug/logger.hpp>
#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>

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

    void initialize(const window_config &cfg);

    void set_monitor(monitor *);
    void set_resolution(const resolution &);
    void set_display_mode(const display_mode_e &);
    void set_framebuffer_size_callback(const std::function<void(int, int)> &);

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

    void load_monitors();

    void detect_primary_monitor();
    void detect_current_monitor();

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
    std::function<void(int, int)> m_app_framebuffer_cb;
};
