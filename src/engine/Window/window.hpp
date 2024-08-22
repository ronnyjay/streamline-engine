#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <engine/Debug/Debuggable.hpp>
#include <engine/Monitor/monitor.hpp>
#include <engine/Resolution/resolution.hpp>

namespace engine
{

class Application;

typedef enum
{
    Fullscreen,
    Windowed,
    Borderless,
} DisplayMode;

class Window : public Debuggable
{
  public:
    Window(const int, const int, const char *, Application *const);

    inline GLFWwindow *const window()
    {
        return window_;
    }

    void refresh();

    void set_monitor(Monitor *);
    void set_resolution(Resolution);
    void set_display_mode(DisplayMode);

    void draw_debug_info() override;

    int x();
    int y();
    int width();
    int height();
    int display_mode();

    Monitor *const primary_monitor() const;
    Monitor *const current_monitor() const;

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

    Monitor *primary_monitor_;
    Monitor *current_monitor_;

    std::vector<Monitor *> monitors_;

    static const char *display_modes_[];

    static void key_callback(GLFWwindow *, int, int, int, int);

    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);

    static void framebuffer_size_callback(GLFWwindow *, int, int);
};

} // namespace engine