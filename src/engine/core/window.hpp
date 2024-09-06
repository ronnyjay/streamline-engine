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

    const std::string ToString() const
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

typedef std::vector<Monitor> MonitorList;

typedef enum
{
    FULLSCREEN = 0,
    WINDOWED   = 1,
    BORDERLESS = 2
} DisplayMode;

class Window
{
  public:
    Window(int, int, const char *);

    operator GLFWwindow *()
    {
        return m_window;
    }

    void Refresh();

    void SetMonitor(int);

    void SetResolution(Resolution);
    void SetDisplayMode(DisplayMode);

    int X() const
    {
        return m_x;
    }

    int Y() const
    {
        return m_y;
    }

    int Width() const
    {
        return m_width;
    }

    int Height() const
    {
        return m_height;
    }

    DisplayMode Mode() const
    {
        return m_mode;
    }

    const Monitor *const CurrentMonitor() const
    {
        return m_current_monitor;
    }

    const Monitor *const PrimaryMonitor() const
    {
        return m_primary_monitor;
    }

    ~Window();

    Window(const Window &)  = delete;
    Window(const Window &&) = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

    template <typename T>
    void on(std::function<void(T &)> fn)
    {
        m_event_register.Register(fn);
    }

  private:
    GLFWwindow *m_window;

    // window attr's
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    DisplayMode m_mode;
    // window attr's

    // available monitors
    MonitorList m_monitors;

    // window defaults to this monitor
    Monitor *m_primary_monitor;

    // window is currently on this monitor
    Monitor *m_current_monitor;

    // window callback register/dispatcher
    EventRegister m_event_register;

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