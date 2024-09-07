#include "window.hpp"
#include "engine/Logger/Logger.hpp"

#include <algorithm>

using namespace engine;

Monitor::Monitor(GLFWmonitor *m)
    : monitor(m)
{
    title = glfwGetMonitorName(m);

    glfwGetMonitorWorkarea(m, &x, &y, &width, &height);
    glfwGetMonitorContentScale(m, &scale.x, &scale.y);

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(m, &count);

    for (int i = 0; i < count; i++)
    {
        resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());

    active_resolutions.fullscreen = resolutions.size() - 1;
    active_resolutions.windowed   = -1;
    active_resolutions.borderless = resolutions.size() - 1;
}

Window::Window(int width, int height, const char *title)
    : m_width(width)
    , m_height(height)
{
    if (!glfwInit())
    {
        Logger::err("Failed to intialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // initialize monitors
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        m_monitors.emplace_back(Monitor(monitors[i]));
    }

    m_primary_monitor = &m_monitors.at(0);
    m_current_monitor = &m_monitors.at(0);

    // initialize window
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (m_window == nullptr)
    {
        Logger::err("Failed to intialize window");
    }

    glfwMakeContextCurrent(m_window);

    glfwGetWindowPos(m_window, &m_x, &m_y);
    glfwGetWindowSize(m_window, &m_width, &m_height);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowAspectRatio(m_window, width, height);

    glfwSetFramebufferSizeCallback(m_window, Window::FramebufferSizeCallback);
    glfwSetWindowIconifyCallback(m_window, Window::MinimizeCallback);
    glfwSetWindowMaximizeCallback(m_window, Window::MaximizeCallback);
    glfwSetKeyCallback(m_window, Window::KeyCallback);
    glfwSetMouseButtonCallback(m_window, Window::MouseCallback);
    glfwSetCursorPosCallback(m_window, Window::CursorPosCallback);
    glfwSetScrollCallback(m_window, Window::ScrollCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        Logger::err("Failed to initialize glad");
    }

    m_mode = WINDOWED;
}

void Window::set_monitor(int monitor)
{
    if (monitor < 0 || static_cast<size_t>(monitor) >= m_monitors.size())
    {
        return;
    }

    m_primary_monitor = &m_monitors.at(monitor);

    if (m_mode != WINDOWED)
    {
        set_display_mode(m_mode);
    }
}

void Window::set_resolution(int width, int height)
{
    if (m_mode == BORDERLESS)
    {
        return;
    }

    m_width  = width;
    m_height = height;

    if (m_mode == FULLSCREEN)
    {
        glfwSetWindowMonitor(m_window, m_primary_monitor->monitor, 0, 0, width, height, 0);

        for (size_t i = 0; i < m_primary_monitor->resolutions.size(); i++)
        {
            if (Resolution(width, height) == m_primary_monitor->resolutions.at(i))
            {
                m_primary_monitor->active_resolutions.fullscreen = i;
            }
        }

        m_primary_monitor->active_resolutions.fullscreen = -1;
    }

    if (m_mode == WINDOWED)
    {
        auto monitor_scale = m_current_monitor->scale;

        glfwSetWindowAspectRatio(m_window, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwSetWindowSize(m_window, width / monitor_scale.x, height / monitor_scale.y);
        glfwSetWindowAspectRatio(m_window, width, height);

        for (size_t i = 0; i < m_current_monitor->resolutions.size(); i++)
        {
            if (Resolution(width, height) == m_current_monitor->resolutions.at(i))
            {
                m_current_monitor->active_resolutions.windowed = i;

                return;
            }
        }

        m_current_monitor->active_resolutions.windowed = -1;
    }
}

void Window::set_display_mode(DisplayMode mode)
{
    if (mode == FULLSCREEN)
    {
        Resolution current = m_primary_monitor->resolutions[m_primary_monitor->active_resolutions.fullscreen];

        glfwSetWindowMonitor(
            m_window,
            nullptr,
            m_primary_monitor->x,
            m_primary_monitor->y,
            m_primary_monitor->width,
            m_primary_monitor->height,
            0);

        glfwSetWindowMonitor(m_window, m_primary_monitor->monitor, 0, 0, current.width, current.height, 0);
    }

    if (mode == BORDERLESS)
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
            0);
    }

    if (mode == WINDOWED)
    {
        if (!glfwGetWindowAttrib(m_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, GL_TRUE);
        }

        if (glfwGetWindowAttrib(m_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, GL_FALSE);
        }

        glfwSetWindowMonitor(m_window, nullptr, m_x, m_y, m_width, m_height, 0);
    }

    m_mode = mode;
}

Window::~Window()
{
    glfwTerminate();
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(WINDOW_RESIZED, WindowResizedEvent(width, height));
}

void Window::MinimizeCallback(GLFWwindow *window, int minimized)
{
    (minimized) ? glfwIconifyWindow(window) : glfwRestoreWindow(window);
}

void Window::MaximizeCallback(GLFWwindow *window, int maximized)
{
    (maximized) ? glfwMaximizeWindow(window) : glfwRestoreWindow(window);
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(KEY_PRESSED, KeyPressedEvent(key, scancode, action, mods));
}

void Window::MouseCallback(GLFWwindow *window, int button, int action, int mods)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(MOUSE_PRESSED, MousePressedEvent(button, action, mods));
}

void Window::CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(MOUSE_MOVED, MouseMovedEvent(xpos, ypos));
}

void Window::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    static_cast<Window *>(glfwGetWindowUserPointer(window))
        ->dispatch(MOUSE_SCROLLED, MouseScrolledEvent(xoffset, yoffset));
}