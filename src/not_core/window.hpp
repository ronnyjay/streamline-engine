#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cstdio>
#include <vector>

#include "debug.hpp"
#include "event.hpp"

namespace engine
{

struct Resolution
{
    Resolution(int width, int height)
        : width(width)
        , height(height)
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

    int         width;
    int         height;

    const char *c_str() const
    {
        std::snprintf(m_format, sizeof(m_format), "%dx%d", width, height);
        return m_format;
    }

  private:
    mutable char m_format[32];
};

struct Monitor
{
    Monitor(GLFWmonitor *, int);

    bool operator==(const Monitor &other)
    {
        return glfwMonitor == other.glfwMonitor;
    }

    bool operator!=(const Monitor &other)
    {
        return glfwMonitor != other.glfwMonitor;
    }

    int number() const
    {
        return m_monitor_number;
    }

    GLFWmonitor *glfwMonitor;

    int          StartX;
    int          StartY;

    int          W;
    int          H;

    struct
    {
        float x;
        float y;
    } Scale;

    const char *Title;

    struct
    {
        int fullscreen;
        int windowed;
        int borderless;
    } resolution;

    std::vector<Resolution> Resolutions;

  private:
    int m_monitor_number;
};

typedef enum
{
    FULLSCREEN = 0,
    WINDOWED   = 1,
    BORDERLESS = 2
} DisplayMode;

class Window
    : public EventDispatcher
    , public Debuggable
{
  public:
    /**
     * @brief
     *
     * @param width
     * @param height
     * @param title
     */
    Window(int width = 800, int height = 600, const char *title = "Untitled Window");

    /**
     * @brief
     *
     * @return GLFWwindow *
     */
    operator GLFWwindow *()
    {
        return m_window;
    }

    /**
     * @brief
     *
     */
    void refresh();

    /**
     * @brief
     *
     * @param number
     */
    void set_monitor(int number);

    /**
     * @brief
     *
     * @param width
     * @param height
     */
    void set_resolution(int width, int height);

    /**
     * @brief
     *
     * @param mode
     */
    void set_display_mode(DisplayMode mode);

    /**
     * @brief
     *
     * @return int
     */
    int x() const
    {
        return m_x;
    }

    /**
     * @brief
     *
     * @return int
     */
    int y() const
    {
        return m_y;
    }

    /**
     * @brief
     *
     * @return int
     */
    int width() const
    {
        return m_width;
    }

    /**
     * @brief
     *
     * @return int
     */
    int height() const
    {
        return m_height;
    }

    /**
     * @brief
     *
     * @return int
     */
    int display_mode() const
    {
        return m_display_mode;
    }

    /**
     * @brief
     *
     * @return const Monitor* const
     */
    const Monitor *const current_monitor() const
    {
        return m_current_monitor;
    }

    /**
     * @brief
     *
     * @return const Monitor* const
     */
    const Monitor *const primary_monitor() const
    {
        return m_primary_monitor;
    }

    DEBUGGABLE()

    /**
     * @brief
     *
     */
    ~Window()
    {
        glfwTerminate();
    }

    Window(const Window &)            = delete;
    Window(const Window &&)           = delete;

    Window operator=(const Window &)  = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow          *m_window;

    int                  m_x;
    int                  m_y;

    int                  m_width;
    int                  m_height;

    int                  m_display_mode;

    Monitor             *m_primary_monitor;
    Monitor             *m_current_monitor;

    std::vector<Monitor> m_monitors;

    static const char   *DISPLAY_MODE_OPTIONS[];

    static void          framebuffer_size_callback(GLFWwindow *, int, int);

    static void          minimize_callback(GLFWwindow *, int);
    static void          maximize_callback(GLFWwindow *, int);

    static void          key_callback(GLFWwindow *, int, int, int, int);
    static void          mouse_callback(GLFWwindow *, int, int, int);

    static void          cursor_pos_callback(GLFWwindow *, double, double);
    static void          scroll_callback(GLFWwindow *, double, double);
};

} // namespace engine