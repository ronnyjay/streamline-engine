#pragma once

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "monitor.hpp"
#include "resolution.hpp"

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
    window(const config &);

    inline GLFWwindow *const glfw_window()
    {
        return window_;
    }

    void refresh();

    void set_monitor(monitor *);
    void set_resolution(resolution);
    void set_display_mode(display_mode_e);

    int x();
    int y();
    int width();
    int height();
    int display_mode();

    monitor *const primary_monitor() const;
    monitor *const current_monitor() const;

  private:
    GLFWwindow *window_;

    int x_;
    int y_;
    int width_;
    int height_;
    int display_mode_;

    int last_width_;
    int last_height_;
    int last_display_mode_;

    monitor *primary_monitor_;
    monitor *current_monitor_;

    std::vector<monitor *> monitors_;

    static const std::string display_modes_strings[];

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
};
