#include <core/window.hpp>
#include <cassert>
#include <cstring>

using namespace engine;

Window *Window::create(int width, int height, const char *title)
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

    glfwSetFramebufferSizeCallback(window, Window::FramebufferSizeCallback);
    glfwSetWindowMaximizeCallback(window, Window::MaximizeCallback);
    glfwSetWindowIconifyCallback(window, Window::MinimizeCallback);
    glfwSetKeyCallback(window, Window::KeyCallback);
    glfwSetMouseButtonCallback(window, Window::MouseButtonCallback);
    glfwSetCursorPosCallback(window, Window::CursorPosCallback);
    glfwSetScrollCallback(window, Window::ScrollCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    return new Window(window);
}

void Window::close()
{
    glfwSetWindowShouldClose(m_base_window, GLFW_TRUE);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_base_window);
}

bool Window::is_open() const
{
    return !glfwWindowShouldClose(m_base_window);
}

bool Window::is_focused() const
{
    return glfwGetWindowAttrib(m_base_window, GLFW_FOCUSED);
}

bool Window::is_decorated() const
{
    return glfwGetWindowAttrib(m_base_window, GLFW_DECORATED);
}

bool Window::is_floating() const
{
    return glfwGetWindowAttrib(m_base_window, GLFW_FLOATING);
}

bool Window::is_resizable() const
{
    return glfwGetWindowAttrib(m_base_window, GLFW_RESIZABLE);
}

Vector2i Window::get_position_in_screen() const
{
    Vector2i position;

    glfwGetWindowPos(m_base_window, &position.x, &position.y);

    return position;
}

Vector2i Window::get_size_in_screen() const
{
    Vector2i size;

    glfwGetWindowSize(m_base_window, &size.x, &size.y);

    return size;
}

void Window::move_to(int x, int y)
{
    if (glfwGetWindowMonitor(m_base_window))
    {
        return;
    }

    m_last_position.x = x;
    m_last_position.y = y;

    glfwSetWindowPos(m_base_window, x, y);
}

void Window::resize(int w, int h)
{
    if (glfwGetWindowMonitor(m_base_window))
    {
        return;
    }

    m_last_size.x = w;
    m_last_size.y = h;

    glfwSetWindowSize(m_base_window, w, h);
}

void Window::set_window_mode(WindowMode m)
{
    if (m_window_mode == WindowMode::Windowed)
    {
        glfwGetWindowPos(m_base_window, &m_last_position.x, &m_last_position.y);
        glfwGetWindowSize(m_base_window, &m_last_size.x, &m_last_size.y);
    }

    if (m == WindowMode::Windowed)
    {
        if (!glfwGetWindowAttrib(m_base_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_base_window, GLFW_DECORATED, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(m_base_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_base_window, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(
            m_base_window, nullptr, m_last_position.x, m_last_position.y, m_last_size.x, m_last_size.y, GLFW_DONT_CARE);

        return;
    }

    GLFWmonitor  *monitor = nullptr;

    int           x, y;
    int           w, h;
    int           count;

    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        glfwGetMonitorWorkarea(monitors[i], &x, &y, &w, &h);

        bool overlap_x = (m_last_position.x >= x && m_last_position.x < x + w);
        bool overlap_y = (m_last_position.y >= y && m_last_position.y < y + h);

        if (overlap_x && overlap_y)
        {
            monitor = monitors[i];
            break;
        }
    }

    if (WindowMode(m) == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(m_base_window, nullptr, x, y, w, h, GLFW_DONT_CARE);
        glfwSetWindowMonitor(m_base_window, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    else if (WindowMode(m) == WindowMode::Borderless)
    {
        if (!glfwGetWindowAttrib(m_base_window, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_base_window, GLFW_FLOATING, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(m_base_window, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_base_window, GLFW_DECORATED, GLFW_FALSE);
        }

        glfwSetWindowMonitor(m_base_window, nullptr, x, y, w, h, GLFW_DONT_CARE);
    }

    m_window_mode = m;
}

Window::~Window()
{
    if (m_base_window)
    {
        glfwDestroyWindow(m_base_window);
        m_base_window = nullptr;
    }

    glfwTerminate();
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        w->m_event_callback(WindowResizeEvent(width, height));
    }
}

void Window::MaximizeCallback(GLFWwindow *window, int maximize)
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

void Window::MinimizeCallback(GLFWwindow *window, int minimize)
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

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
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

void Window::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
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

void Window::CursorPosCallback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        w->m_event_callback(MouseMoveEvent(x, y));
    }
}

void Window::ScrollCallback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->m_event_callback)
    {
        w->m_event_callback(MouseScrollEvent(x, y));
    }
}
