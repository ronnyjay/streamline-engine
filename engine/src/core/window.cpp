#include "core/window.hpp"

using namespace engine;

window::window(int width, int height, const char *title)
    : m_windowMode(window_mode::windowed)
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

    glfwSetFramebufferSizeCallback(m_glfwWindow, window::framebuffer_callback);
    glfwSetWindowMaximizeCallback(m_glfwWindow, window::maximize_callback);
    glfwSetWindowIconifyCallback(m_glfwWindow, window::minimize_callback);
    glfwSetKeyCallback(m_glfwWindow, window::key_callback);
    glfwSetMouseButtonCallback(m_glfwWindow, window::mouse_callback);
    glfwSetCursorPosCallback(m_glfwWindow, window::cursor_callback);
    glfwSetScrollCallback(m_glfwWindow, window::scroll_callback);

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

bool window::isOpen() const
{
    return !glfwWindowShouldClose(m_glfwWindow);
}

bool window::isVisible() const
{
    return glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE);
}

void window::show()
{
    glfwShowWindow(m_glfwWindow);
}

void window::hide()
{
    glfwHideWindow(m_glfwWindow);
}

void window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

void window::pollEvents()
{
    glfwPollEvents();
}

void window::toggleCursor()
{
    m_cursorFlags.visible = !m_cursorFlags.visible;

    if (m_cursorFlags.visible)
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    m_cursorFlags.entered = true;
}

const ivec2 &window::getPositionInScreen() const
{
    return m_lastPos;
}

const ivec2 &window::getSizeInScreen() const
{
    return m_lastSize;
}

void window::moveTo(int x, int y)
{
    // window fullscreen; do not move.
    if (glfwGetWindowMonitor(m_glfwWindow))
    {
        return;
    }

    // store last position for windowed mode
    if (m_windowMode == window_mode::windowed)
    {
        m_lastPos.x = x;
        m_lastPos.y = y;
    }

    glfwSetWindowPos(m_glfwWindow, x, y);
}

void window::resize(int x, int y)
{
    // window fullscreen; do not resize.
    if (glfwGetWindowMonitor(m_glfwWindow))
    {
        return;
    }

    // store last size for windowed mode
    if (m_windowMode == window_mode::windowed)
    {
        m_lastSize.x = x;
        m_lastSize.y = y;
    }

    glfwSetWindowSize(m_glfwWindow, x, y);
}

void window::setWindowMode(window_mode mode)
{
    if (m_windowMode == window_mode::windowed)
    {
        glfwGetWindowPos(m_glfwWindow, &m_lastPos.x, &m_lastPos.y);
        glfwGetWindowSize(m_glfwWindow, &m_lastSize.x, &m_lastSize.y);
    }

    m_windowMode = mode;

    if (mode == window_mode::windowed)
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

    GLFWmonitor *monitor = nullptr;

    int x, y;
    int w, h;
    int count;

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

    if (mode == window_mode::fullscreen)
    {
        glfwSetWindowMonitor(m_glfwWindow, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    if (mode == window_mode::windowed_fullscreen)
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

void window::framebuffer_callback(GLFWwindow *glfwWindow, int width, int height)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfwWindow));

    if (w->m_eventCallback)
    {
        w->m_eventCallback(window_resize_event(width, height));
    }
}

void window::maximize_callback(GLFWwindow *glfwWindow, int maximize)
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

void window::minimize_callback(GLFWwindow *glfwWindow, int minimize)
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

void window::key_callback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfwWindow));

    /** TODO: convert key code to engine key  */

    if (w->m_eventCallback)
    {
        if (action == GLFW_RELEASE)
        {
            w->m_eventCallback(key_release_event(key));
        }
        else
        {
            w->m_eventCallback(key_press_event(key, mods, action == GLFW_REPEAT));
        }
    }
}

void window::mouse_callback(GLFWwindow *glfwWindow, int button, int action, int mods)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfwWindow));

    if (w->m_eventCallback)
    {
        if (action == GLFW_PRESS)
        {
            w->m_eventCallback(mouse_button_press_event(button));
        }
        else
        {
            w->m_eventCallback(mouse_button_release_event(button));
        }
    }
}

void window::cursor_callback(GLFWwindow *glfwWindow, double xposIn, double yposIn)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfwWindow));

    if (w->m_eventCallback)
    {
        auto size = w->getSizeInScreen();

        static float lastX = size.x / 2.0f;
        static float lastY = size.y / 2.0f;

        if (w->m_cursorFlags.entered)
        {
            lastX = xposIn;
            lastY = yposIn;

            w->m_cursorFlags.entered = false;
        }

        float xPos = static_cast<float>(xposIn);
        float yPos = static_cast<float>(yposIn);

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;

        w->m_eventCallback(mouse_move_event(xOffset, yOffset));
    }
}

void window::scroll_callback(GLFWwindow *glfwWindow, double xoffset, double yoffset)
{
    window *w = static_cast<window *>(glfwGetWindowUserPointer(glfwWindow));

    if (w->m_eventCallback)
    {
        w->m_eventCallback(mouse_scroll_event(xoffset, yoffset));
    }
}
