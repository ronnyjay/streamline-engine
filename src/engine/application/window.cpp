#include "window.hpp"

#include <GLFW/glfw3.h>
#include <functional>
#include <libstreamline/debug/logger.hpp>

void window::on_resize(resize_event::callback callback)
{
    m_on_resize = callback;
}

void window::on_minimize(minimize_event::callback callback)
{
    m_on_minimize = callback;
}

void window::on_maximize(maximize_event::callback callback)
{
    m_on_maximize = callback;
}

void window::initialize(const window_config &cfg)
{
    m_cfg = cfg;

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, window::framebuffer_size_callback);
    glfwSetMouseButtonCallback(m_window, window::mouse_press_callback);
    glfwSetCursorPosCallback(m_window, window::mouse_pos_callback);

    load_monitors();

    detect_primary_monitor();
    detect_current_monitor();

    set_monitor(m_primary_monitor);
    glfwSwapInterval(cfg.vsync);

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

void window::set_resolution(const resolution &res)
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

void window::set_display_mode(const display_mode_e &mode)
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

void window::key_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));

    if (w->m_on_key_press)
    {
        w->m_on_key_press(key_press_event(key, scancode, action, mods));
    }
}

void window::cursor_callback(GLFWwindow *glfw_window, double xpos_in, double ypos_in)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));
}

void window::scroll_callback(GLFWwindow *glfw_window, double x_offset, double y_offset)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));
}

void window::minimize_callback(GLFWwindow *glfw_window, int minimize)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));

    // glfw logic
    // the window should do this automatically
    if (minimize)
    {
        glfwIconifyWindow(glfw_window);
    }
    else
    {
        glfwRestoreWindow(glfw_window);
    }

    if (w->m_on_minimize)
    {
        w->m_on_minimize(minimize_event(minimize));
    }
}

void window::maximize_callback(GLFWwindow *glfw_window, int maximize)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));

    // glfw logic
    // the window should do this automatically
    if (maximize)
    {
        glfwMaximizeWindow(glfw_window);
    }
    else
    {
        glfwRestoreWindow(glfw_window);
    }

    if (w->m_on_maximize)
    {
        w->m_on_maximize(maximize_event(maximize));
    }
}

void window::framebuffer_size_callback(GLFWwindow *glfw_window, int width, int height)
{
    glViewport(0, 0, width, height);

    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfw_window));

    if (w->m_on_resize)
    {
        w->m_on_resize(resize_event(width, height));
    }
}

void window::set_mouse_press_callback(const std::function<void(int, int, int)> &cb)
{
    m_app_mouse_press_cb = cb;
}

void window::mouse_press_callback(GLFWwindow *glfwWindow, int button, int action, int mods)
{
    window *w = static_cast<class window *>(glfwGetWindowUserPointer(glfwWindow));
    w->m_app_mouse_press_cb(button, action, mods);
}

void window::set_mouse_pos_callback(const std::function<void(double, double)> &cb)
{
    m_app_mouse_pos_cb = cb;
}

void window::mouse_pos_callback(GLFWwindow *glfwWindow, double x, double y)
{
    window *w = static_cast<class window *>(glfwGetWindowUserPointer(glfwWindow));
    w->m_app_mouse_pos_cb(x, y);
}
