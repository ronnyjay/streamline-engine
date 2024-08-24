#include "window.hpp"

#include <libstreamline/debug/logger.hpp>

void window::initialize(const window_config &cfg)
{
    m_cfg = cfg;

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
    m_window = glfwCreateWindow(cfg.width, cfg.height, "Streamline Engine", NULL, NULL);

    if (!m_window)
    {
        m_log.err("failed to initialize window");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        m_log.err("failed to initialize glad");
    }

    load_monitors();

    detect_primary_monitor();
    detect_current_monitor();

    m_log.info("initialized window");
}

void window::refresh()
{
    detect_current_monitor();
}

void window::set_monitor(monitor *monitor)
{
    m_primary_monitor = monitor;

    if (m_cfg.display_mode == FULLSCREEN || m_cfg.display_mode == BORDERLESS)
    {
        set_display_mode(static_cast<display_mode_e>(m_cfg.display_mode));
    }
}

void window::set_resolution(resolution res)
{
    if (m_cfg.display_mode == FULLSCREEN)
    {
        glfwSetWindowMonitor(m_window, m_primary_monitor->glfw_monitor, 0, 0, res.width, res.height, GLFW_DONT_CARE);

        bool found = false;

        for (size_t i = 0; i < m_primary_monitor->resolutions.size(); ++i)
        {
            if (m_primary_monitor->resolutions.at(i) == res)
            {
                found = true;

                m_primary_monitor->active_resolutions.fullscreen = i;
            }
        }

        if (!found)
        {
            m_primary_monitor->active_resolutions.fullscreen = -1;
        }
    }
    else if (m_cfg.display_mode == WINDOWED)
    {
        glfwSetWindowAspectRatio(m_window, GLFW_DONT_CARE, GLFW_DONT_CARE); // remove aspect ratio lock
        glfwSetWindowSize(m_window, res.width / m_current_monitor->scale.x, res.height / m_current_monitor->scale.y);
        glfwSetWindowAspectRatio(m_window, res.width, res.height);

        bool found = false;

        for (size_t i = 0; i < m_current_monitor->resolutions.size(); ++i)
        {
            if (m_current_monitor->resolutions[i] == res)
            {
                found = true;

                m_current_monitor->active_resolutions.windowed = i;
            }
        }

        if (!found)
        {
            m_current_monitor->active_resolutions.windowed = -1;
        }
    }
}

void window::set_display_mode(display_mode_e mode)
{
    // store window's position and size
    if (m_last_display_mode == WINDOWED)
    {
        glfwGetWindowPos(m_window, &m_x, &m_y);
        glfwGetWindowSize(m_window, &m_last_width, &m_last_height);
    }

    if (mode == FULLSCREEN)
    {
        resolution current = m_primary_monitor->resolutions[m_primary_monitor->active_resolutions.fullscreen];

        // set monitor null before setting to primary
        // ... fixes issues with linux
        glfwSetWindowMonitor(
            m_window,
            nullptr,
            m_primary_monitor->x,
            m_primary_monitor->y,
            m_primary_monitor->width,
            m_primary_monitor->height,
            GLFW_DONT_CARE);

        glfwSetWindowMonitor(
            m_window, m_primary_monitor->glfw_monitor, 0, 0, current.width, current.height, GLFW_DONT_CARE);
    }
    else if (mode == WINDOWED)
    {
        if (!glfwGetWindowAttrib(m_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, GL_TRUE);
        }

        if (glfwGetWindowAttrib(m_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, GL_FALSE);
        }

        // restore window's last position and size
        glfwSetWindowMonitor(m_window, nullptr, m_x, m_y, m_last_width, m_last_height, GLFW_DONT_CARE);
    }
    else if (mode == BORDERLESS)
    {
        if (glfwGetWindowAttrib(m_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, GL_FALSE);
        }

        if (!glfwGetWindowAttrib(m_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, GL_TRUE);
        }

        glfwSetWindowMonitor(
            m_window,
            nullptr,
            m_primary_monitor->x,
            m_primary_monitor->y,
            m_primary_monitor->width,
            m_primary_monitor->height,
            GLFW_DONT_CARE);
    }

    m_last_display_mode = mode;
}

void window::load_monitors()
{
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        m_monitors.emplace_back(new monitor(monitors[i]));
    }
}

void window::detect_primary_monitor()
{
    bool found = false;

    for (auto *monitor : m_monitors)
    {
        if (monitor->title == m_cfg.monitor)
        {
            found = true;

            m_primary_monitor = monitor;

            m_log.info("detected primary monitor: %s", m_primary_monitor->title);
        }
    }

    if (!found)
    {
        m_log.info("specified primary monitor not found: %s", m_cfg.monitor.c_str());

        m_primary_monitor = m_monitors.at(0);

        m_log.info("reverting to default monitor for primary monitor: %s", m_primary_monitor->title);
    }
}

void window::detect_current_monitor()
{
    bool found = false;

    glfwGetWindowPos(m_window, &m_x, &m_y);

    for (size_t i = 0; i < m_monitors.size(); i++)
    {
        auto monitor = m_monitors[i];

        bool overlap_x = m_x >= monitor->x && m_x < monitor->x + monitor->width;
        bool overlap_y = m_y >= monitor->y && m_y < monitor->y + monitor->height;

        if (overlap_x && overlap_y)
        {
            found = true;

            m_current_monitor = m_monitors[i];

            m_log.info("detected current monitor: %s", m_current_monitor->title);
        }
    }

    if (!found)
    {
        m_log.info("unable to detect current monintor");

        m_current_monitor = m_primary_monitor;

        m_log.info("reverting to default monitor for current monitor: %s", m_primary_monitor->title);
    }
}

void window::key_callback(GLFWwindow *, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
    }
}

void window::cursor_callback(GLFWwindow *, double xpos_in, double ypos_in)
{
}

void window::scroll_callback(GLFWwindow *, double x_offset, double y_offset)
{
}

static void minimize_callback(GLFWwindow *, int minimize)
{
}

static void maximize_callback(GLFWwindow *, int maximize)
{
}

static void framebuffer_size_callback(GLFWwindow *, int width, int height)
{
}