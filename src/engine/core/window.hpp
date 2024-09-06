#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cstdio>
#include <format>
#include <vector>

#include "event.hpp"

namespace engine
{

struct Resolution
{
    Resolution(int w, int h)
        : width(w)
        , height(h)
    {
    }

    bool operator==(const Resolution &other) const
    {
        return width == other.width && height == other.height;
    }

    bool operator<(const Resolution &other) const
    {
        if (width != other.width)
        {
            return width < other.width;
        }

        return height < other.height;
    }

    int width;
    int height;

    const std::string to_string() const
    {
        return std::format("{}x{}", width, height);
    }
};

struct Monitor
{
    Monitor(GLFWmonitor *m);

    bool operator==(const Monitor &other)
    {
        return monitor == other.monitor;
    }

    bool operator!=(const Monitor &other)
    {
        return monitor != other.monitor;
    }

    GLFWmonitor *monitor;

    int x;
    int y;

    int width;
    int height;

    struct
    {
        float x;
        float y;
    } scale;

    const char *title;

    struct
    {
        int fullscreen;
        int windowed;
        int borderless;
    } active_resolutions;

    std::vector<Resolution> resolutions;
};

typedef enum
{
    FULLSCREEN = 0,
    WINDOWED   = 1,
    BORDERLESS = 2
} DisplayMode;

class Window : public EventDispatcher
{
  public:
    Window(int, int, const char *);

    operator GLFWwindow *()
    {
        return m_window;
    }

    void refresh();

    void set_monitor(int);
    void set_resolution(int, int);

    void set_display_mode(DisplayMode);

    int x() const
    {
        return m_x;
    }

    int y() const
    {
        return m_y;
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    int display_mode() const
    {
        return m_mode;
    }

    const Monitor *const current_monitor() const
    {
        return m_current_monitor;
    }

    const Monitor *const primary_monitor() const
    {
        return m_primary_monitor;
    }

    ~Window();

    Window(const Window &)  = delete;
    Window(const Window &&) = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow *m_window;

    int m_x;
    int m_y;

    int m_width;
    int m_height;

    DisplayMode m_mode;

    Monitor *m_primary_monitor;
    Monitor *m_current_monitor;

    std::vector<Monitor> m_monitors;

  private:
    static void FramebufferSizeCallback(GLFWwindow *, int, int);

    static void MinimizeCallback(GLFWwindow *, int);
    static void MaximizeCallback(GLFWwindow *, int);

    static void KeyCallback(GLFWwindow *, int, int, int, int);
    static void MouseCallback(GLFWwindow *, int, int, int);

    static void CursorPosCallback(GLFWwindow *, double, double);
    static void ScrollCallback(GLFWwindow *, double, double);
};

} // namespace engine