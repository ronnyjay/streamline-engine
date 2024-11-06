#include "window.hpp"
#include <cassert>
#include <cstring>

using namespace engine;

std::unique_ptr<Window> Window::create(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
    glfwSetWindowMaximizeCallback(window, Window::window_maximize_callback);
    glfwSetWindowIconifyCallback(window, Window::window_minimize_callback);
    glfwSetKeyCallback(window, Window::key_callback);
    glfwSetMouseButtonCallback(window, Window::mouse_button_callback);
    glfwSetCursorPosCallback(window, Window::cursor_pos_callback);
    glfwSetScrollCallback(window, Window::scroll_callback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    return std::unique_ptr<Window>(new Window(window));
}

void Window::move_to(int x, int y)
{
    if (glfwGetWindowMonitor(m_window))
    {
        return;
    }

    m_x = x;
    m_y = y;

    glfwSetWindowPos(m_window, x, y);
}

void Window::resize(int w, int h)
{
    if (glfwGetWindowMonitor(m_window))
    {
        return;
    }

    m_width  = w;
    m_height = h;

    glfwSetWindowSize(m_window, w, h);
}

void Window::set_window_mode(WindowMode m)
{
    GLFWmonitor  *monitor = nullptr;

    int           x, y;
    int           w, h;
    int           count;

    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        glfwGetMonitorWorkarea(monitors[i], &x, &y, &w, &h);

        bool overlap_x = (m_x >= x && m_x < x + w);
        bool overlap_y = (m_y >= y && m_y < y + h);

        if (overlap_x && overlap_y)
        {
            monitor = monitors[i];
            break;
        }
    }

    if (WindowMode(m) == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(m_window, nullptr, x, y, w, h, GLFW_DONT_CARE);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    else if (WindowMode(m) == WindowMode::Windowed)
    {
        if (!glfwGetWindowAttrib(m_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(m_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(
            m_window,
            nullptr,
            // Center the window on the primary monitor
            // Later, track the window's last x, y to restore last position
            x + (w - m_width) / 2,
            y + (h - m_height) / 2,
            m_width,
            m_height,
            GLFW_DONT_CARE);
    }

    else if (WindowMode(m) == WindowMode::Borderless)
    {
        if (!glfwGetWindowAttrib(m_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(m_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
        }

        glfwSetWindowMonitor(m_window, nullptr, x, y, w, h, GLFW_DONT_CARE);
    }
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    Window *w   = static_cast<Window *>(glfwGetWindowUserPointer(window));

    w->m_width  = width;
    w->m_height = height;

    if (w->m_event_callback)
    {
        w->m_event_callback(WindowResizeEvent(width, height));
    }
}

void Window::window_maximize_callback(GLFWwindow *window, int maximize)
{
    if (maximize)
    {
        glfwMaximizeWindow(window);
    }
    else
    {
        glfwRestoreWindow(window);
    }
}

void Window::window_minimize_callback(GLFWwindow *window, int minimize)
{
    if (minimize)
    {
        glfwIconifyWindow(window);
    }
    else
    {
        glfwRestoreWindow(window);
    }
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        if (action == GLFW_RELEASE)
        {
            w->m_event_callback(KeyReleaseEvent(key));
        }
        else
        {
            w->m_event_callback(KeyPressEvent(key, mods, action == GLFW_REPEAT));
        }
    }
}

void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        if (action == GLFW_PRESS)
        {
            w->m_event_callback(MouseButtonPressEvent(button));
        }
        else
        {
            w->m_event_callback(MouseButtonReleaseEvent(button));
        }
    }
}

void Window::cursor_pos_callback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        w->m_event_callback(MouseMoveEvent(x, y));
    }
}

void Window::scroll_callback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        w->m_event_callback(MouseScrollEvent(x, y));
    }
}
