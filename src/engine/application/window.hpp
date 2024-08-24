#pragma once

#include <libstreamline/exception/exception.hpp>
#include <libstreamline/json/json.hpp>
#include <source_location>

#include "libstreamline/debug/logger.hpp"
#include "monitor.hpp"
#include "resolution.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

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

struct window_config
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int display_mode = DEFAULT_DISPLAYMODE;
    int monitor = DEFAULT_MONITOR;
    int vsync = DEFAULT_VSYNC;

    int first_mouse = DEFAULT_FIRST_MOUSE;
    int capture_mouse = DEFAULT_CAPTURE_MOUSE;

    int show_cursor = DEFAULT_SHOW_CURSOR;
    int show_wireframes = DEFAULT_SHOW_WIREFRAMES;
    int show_collisions = DEFAULT_SHOW_COLLISIONS;
    int show_debug_window = DEFAULT_SHOW_DEBUG_WINDOW;
    int show_debug_metrics = DEFAULT_SHOW_DEBUG_METRICS;

    void export_to_file()
    {
        throw unimplemented_exception(std::source_location::current());
    }

    void load(const json_object &)
    {
        throw unimplemented_exception(std::source_location::current());
    }

  private:
    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;
    static constexpr int DEFAULT_DISPLAYMODE = display_mode_e::WINDOWED;
    static constexpr int DEFAULT_MONITOR = 0;
    static constexpr bool DEFAULT_VSYNC = true;

    static constexpr bool DEFAULT_FIRST_MOUSE = true;
    static constexpr bool DEFAULT_CAPTURE_MOUSE = true;

    static constexpr bool DEFAULT_SHOW_CURSOR = false;
    static constexpr bool DEFAULT_SHOW_WIREFRAMES = false;
    static constexpr bool DEFAULT_SHOW_COLLISIONS = false;
    static constexpr bool DEFAULT_SHOW_DEBUG_WINDOW = false;
    static constexpr bool DEFAULT_SHOW_DEBUG_METRICS = false;
};

class window
{
  public:
    window()
      : m_log("Window") {}

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

    static const std::string display_modes_strings[];

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
};
