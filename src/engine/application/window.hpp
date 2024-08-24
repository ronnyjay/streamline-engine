#pragma once

#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>
#include <libstreamline/debug/logger.hpp>

#include "window_config.hpp"
#include "monitor.hpp"
#include "resolution.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

class window
{
  public:
    window()
      : m_log("window") {}

    void initialize(const window_config &cfg);

    void set_monitor(monitor *);
    void set_resolution(resolution);
    void set_display_mode(display_mode_e);

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

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
};
