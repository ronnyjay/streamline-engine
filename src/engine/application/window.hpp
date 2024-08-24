#pragma once

#pragma once

#include "monitor.hpp"
#include "resolution.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <libstreamline/config/config.hpp>

typedef enum
{
    FULLSCREEN,
    WINDOWED,
    BORDERLESS
} display_mode_e;

typedef enum
{
    FPS_30 = 30,
    FPS_60 = 60,
    FPS_120 = 120,
    FPS_144 = 144,
    FPS_165 = 165,
    FPS_240 = 240,
    FPS_360 = 360,
    FPS_UNLIMITED
} framerate_e;

class window
{
  public:
    window() = default;

    void initialize(const config &);

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
        return m_width;
    }

    int height()
    {
        return m_height;
    }

    int display_mode()
    {
        return m_display_mode;
    }

    monitor *const primary_monitor() const
    {
        return m_primary_monitor;
    }

    monitor *const current_monitor() const
    {
        return m_current_monitor;
    }

  private:
    GLFWwindow *m_window;

    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_display_mode;

    int m_last_width;
    int m_last_height;
    int m_last_display_mode;

    monitor *m_primary_monitor;
    monitor *m_current_monitor;

    std::vector<monitor *> m_monitors;

    static const std::string display_modes_strings[];

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
};
