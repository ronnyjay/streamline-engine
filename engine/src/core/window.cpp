#include "core/window.hpp"

using namespace engine;

Window::Window(int width, int height, const char *title)
    : m_windowMode(WindowMode::Windowed)
{
    STREAMLINE_ASSERT(glfwInit(), "Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!m_glfwWindow)
    {
        glfwTerminate();
        STREAMLINE_ASSERT(false, "Failed to create GLFW window");
    }

    glfwSetFramebufferSizeCallback(m_glfwWindow, Window::framebufferCallback);
    glfwSetWindowMaximizeCallback(m_glfwWindow, Window::maximizeCallback);
    glfwSetWindowIconifyCallback(m_glfwWindow, Window::minimizeCallback);
    glfwSetKeyCallback(m_glfwWindow, Window::keyCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, Window::mouseCallback);
    glfwSetCursorPosCallback(m_glfwWindow, Window::cursorCallback);
    glfwSetScrollCallback(m_glfwWindow, Window::scrollCallback);

    glfwGetWindowPos(m_glfwWindow, &m_lastPos.x, &m_lastPos.y);
    glfwGetWindowSize(m_glfwWindow, &m_lastSize.x, &m_lastSize.y);

    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        STREAMLINE_ASSERT(false, "Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(m_glfwWindow, this);
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(m_glfwWindow);
}

bool Window::isVisible() const
{
    return glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE);
}

void Window::show()
{
    glfwShowWindow(m_glfwWindow);
}

void Window::hide()
{
    glfwHideWindow(m_glfwWindow);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::toggleCursor()
{
    m_windowFlags.mouseVisible = !m_windowFlags.mouseVisible;

    if (m_windowFlags.mouseVisible)
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    m_windowFlags.mouseEntered = true;
}

const ivec2 &Window::getPositionInScreen() const
{
    return m_lastPos;
}

const ivec2 &Window::getSizeInScreen() const
{
    return m_lastSize;
}

void Window::moveTo(int x, int y)
{
    // window fullscreen; do not move.
    if (glfwGetWindowMonitor(m_glfwWindow))
    {
        return;
    }

    // store last position for windowed mode
    if (m_windowMode == WindowMode::Windowed)
    {
        m_lastPos.x = x;
        m_lastPos.y = y;
    }

    glfwSetWindowPos(m_glfwWindow, x, y);
}

void Window::resize(int x, int y)
{
    // window fullscreen; do not resize.
    if (glfwGetWindowMonitor(m_glfwWindow))
    {
        return;
    }

    // store last size for windowed mode
    if (m_windowMode == WindowMode::Windowed)
    {
        m_lastSize.x = x;
        m_lastSize.y = y;
    }

    glfwSetWindowSize(m_glfwWindow, x, y);
}

void Window::setWindowMode(WindowMode mode)
{
    if (m_windowMode == WindowMode::Windowed)
    {
        glfwGetWindowPos(m_glfwWindow, &m_lastPos.x, &m_lastPos.y);
        glfwGetWindowSize(m_glfwWindow, &m_lastSize.x, &m_lastSize.y);
    }

    m_windowMode = mode;

    if (mode == WindowMode::Windowed)
    {

        if (!glfwGetWindowAttrib(m_glfwWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_glfwWindow, GLFW_DECORATED, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(m_glfwWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_glfwWindow, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(m_glfwWindow, nullptr, m_lastPos.x, m_lastPos.y, m_lastSize.x, m_lastSize.y, 0);

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

        bool overlap_x = (m_lastPos.x >= x && m_lastPos.x < x + w);
        bool overlap_y = (m_lastPos.y >= y && m_lastPos.y < y + h);

        if (overlap_x && overlap_y)
        {
            monitor = monitors[i];
            break;
        }
    }

    if (mode == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(m_glfwWindow, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    if (mode == WindowMode::WindowedFullscreen)
    {
        if (glfwGetWindowAttrib(m_glfwWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(m_glfwWindow, GLFW_DECORATED, GLFW_TRUE);
        }

        if (!glfwGetWindowAttrib(m_glfwWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(m_glfwWindow, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(m_glfwWindow, nullptr, x, y, w, h, GLFW_DONT_CARE);
    }
}

void Window::framebufferCallback(GLFWwindow *glfwWindow, int width, int height)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        window->m_eventCallback(window_resize_event(width, height));
    }
}

void Window::maximizeCallback(GLFWwindow *glfwWindow, int maximize)
{
    if (maximize)
    {
        glfwMaximizeWindow(glfwWindow);
    }
    else
    {
        glfwRestoreWindow(glfwWindow);
    }
}

void Window::minimizeCallback(GLFWwindow *glfwWindow, int minimize)
{
    if (minimize)
    {
        glfwIconifyWindow(glfwWindow);
    }
    else
    {
        glfwRestoreWindow(glfwWindow);
    }
}

void Window::keyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    /** TODO: convert key code to engine key  */

    if (window->m_eventCallback)
    {
        if (action == GLFW_RELEASE)
        {
            window->m_eventCallback(key_release_event(key));
        }
        else
        {
            window->m_eventCallback(key_press_event(key, mods, action == GLFW_REPEAT));
        }
    }
}

void Window::mouseCallback(GLFWwindow *glfwWindow, int button, int action, int mods)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        if (action == GLFW_PRESS)
        {
            window->m_eventCallback(mouse_button_press_event(button));
        }
        else
        {
            window->m_eventCallback(mouse_button_release_event(button));
        }
    }
}

void Window::cursorCallback(GLFWwindow *glfwWindow, double xposIn, double yposIn)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        auto         size  = window->getSizeInScreen();

        static float lastX = size.x / 2.0f;
        static float lastY = size.y / 2.0f;

        if (window->m_windowFlags.mouseEntered)
        {
            lastX                              = xposIn;
            lastY                              = yposIn;

            window->m_windowFlags.mouseEntered = false;
        }

        float xPos    = static_cast<float>(xposIn);
        float yPos    = static_cast<float>(yposIn);

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;

        window->m_eventCallback(mouse_move_event(xOffset, yOffset));
    }
}

void Window::scrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        window->m_eventCallback(mouse_scroll_event(xoffset, yoffset));
    }
}
