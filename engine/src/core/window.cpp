#include "core/window.hpp"
#include "core/event.hpp"
#include "core/logger.hpp"

#include <GLFW/glfw3.h>
#include <tuple>

using namespace engine;

Window::Window(int width, int height, const char *title)
    : m_windowMode(WindowMode::Windowed)
{
    STREAMLINE_ASSERT(glfwInit(), "Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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

    glfwSetWindowUserPointer(m_glfwWindow, this);

    glfwSetFramebufferSizeCallback(m_glfwWindow, Window::framebufferCallback);
    glfwSetWindowMaximizeCallback(m_glfwWindow, Window::maximizeCallback);
    glfwSetWindowIconifyCallback(m_glfwWindow, Window::minimizeCallback);
    glfwSetKeyCallback(m_glfwWindow, Window::keyCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, Window::mouseCallback);
    glfwSetCursorPosCallback(m_glfwWindow, Window::cursorCallback);
    glfwSetScrollCallback(m_glfwWindow, Window::scrollCallback);

    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        STREAMLINE_ASSERT(false, "Failed to initialize GLAD");
    }

    Logger::info("Initialized GLFW Window");
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

void Window::close()
{
    glfwSetWindowShouldClose(m_glfwWindow, GLFW_TRUE);
}

void Window::showCursor()
{
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::hideCursor()
{
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

std::tuple<int, int> Window::getPositionInScreen() const
{
    int xpos;
    int ypos;
    glfwGetWindowPos(m_glfwWindow, &xpos, &ypos);

    return std::make_tuple(xpos, ypos);
}

std::tuple<int, int> Window::getSizeInScreen() const
{
    int width;
    int height;
    glfwGetWindowSize(m_glfwWindow, &width, &height);

    return std::make_tuple(width, height);
}

WindowMode Window::getWindowMode() const
{
    return m_windowMode;
}

void Window::moveTo(int x, int y)
{
    // window fullscreen - do not move.
    if (glfwGetWindowMonitor(m_glfwWindow))
    {
        return;
    }

    glfwSetWindowPos(m_glfwWindow, x, y);
}

void Window::resize(int x, int y)
{
    glfwSetWindowSize(m_glfwWindow, x, y);
}

void Window::setWindowMode(WindowMode mode)
{
    // clang-format off
    auto [windowX, windowY] = getPositionInScreen();
    auto [windowWidth, windowHeight] = getSizeInScreen();

    GLFWmonitor  *monitor   = nullptr;
    int           count;
    GLFWmonitor **monitors  = glfwGetMonitors(&count);

    int           monitorX, monitorY;
    int           monitorWidth, monitorHeight;

    for (int i = 0; i < count; i++)
    {
        glfwGetMonitorWorkarea(monitors[i], &monitorX, &monitorY, &monitorWidth, &monitorHeight);

        bool overlapX = (windowX >= monitorX && windowX < monitorX + monitorWidth);
        bool overlapY = (windowY >= monitorY && windowY < monitorY + monitorHeight);

        if (overlapX && overlapY)
        {
            monitor = monitors[i];
            break;
        }
    }
    // clang-format on

    if (!monitor)
    {
        return;
    }

    uint32_t nextWindowX = 0;
    uint32_t nextWindowY = 0;

    uint32_t spaceX      = (monitorWidth - windowWidth);
    uint32_t spaceY      = (monitorHeight - windowHeight);

    if (spaceX > 0 && spaceY > 0)
    {
        nextWindowX = spaceX / 2.0f;
        nextWindowY = spaceY / 2.0f;
    }

    m_windowMode = mode;

    if (mode == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(m_glfwWindow, monitor, 0, 0, monitorWidth, monitorHeight, GLFW_DONT_CARE);
    }
    else
    {
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
        }

        if (mode == WindowMode::WindowedFullscreen)
        {
            if (glfwGetWindowAttrib(m_glfwWindow, GLFW_DECORATED))
            {
                glfwSetWindowAttrib(m_glfwWindow, GLFW_DECORATED, GLFW_FALSE);
            }

            if (!glfwGetWindowAttrib(m_glfwWindow, GLFW_FLOATING))
            {
                glfwSetWindowAttrib(m_glfwWindow, GLFW_FLOATING, GLFW_TRUE);
            }
        }

        glfwSetWindowMonitor(m_glfwWindow, nullptr, nextWindowX, nextWindowY, windowWidth, windowHeight, 0);
    }
}

void Window::framebufferCallback(GLFWwindow *glfwWindow, int width, int height)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        window->m_eventCallback(WindowResizeEvent(width, height));
    }

    window->flags.b_mouseEntered = true;
}

void Window::maximizeCallback(GLFWwindow *glfwWindow, int maximize)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (maximize)
    {
        glfwMaximizeWindow(glfwWindow);
    }
    else
    {
        glfwRestoreWindow(glfwWindow);
    }

    window->flags.b_mouseEntered = true;

    if (window->m_eventCallback)
    {
        window->m_eventCallback(WindowMaximizeEvent(maximize));
    }
}

void Window::minimizeCallback(GLFWwindow *glfwWindow, int minimize)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (minimize)
    {
        glfwIconifyWindow(glfwWindow);
    }
    else
    {
        glfwRestoreWindow(glfwWindow);
    }

    window->flags.b_mouseEntered = true;

    if (window->m_eventCallback)
    {
        window->m_eventCallback(WindowMinimizeEvent(minimize));
    }
}

void Window::keyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        if (action == GLFW_RELEASE)
        {
            window->m_eventCallback(KeyReleaseEvent(key));
        }
        else
        {
            window->m_eventCallback(KeyPressEvent(key, mods, action == GLFW_REPEAT));
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
            window->m_eventCallback(MouseButtonPressEvent(button));
        }
        else
        {
            window->m_eventCallback(MouseButtonReleaseEvent(button));
        }
    }
}

void Window::cursorCallback(GLFWwindow *glfwWindow, double xposIn, double yposIn)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        auto [width, height] = window->getSizeInScreen();

        static float lastX   = width / 2.0f;
        static float lastY   = height / 2.0f;

        if (window->flags.b_mouseEntered)
        {
            lastX                        = xposIn;
            lastY                        = yposIn;

            window->flags.b_mouseEntered = false;
        }

        float xPos    = static_cast<float>(xposIn);
        float yPos    = static_cast<float>(yposIn);

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;

        lastX         = xPos;
        lastY         = yPos;

        window->m_eventCallback(MouseMoveEvent(xOffset, yOffset));
    }
}

void Window::scrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (window->m_eventCallback)
    {
        window->m_eventCallback(MouseScrollEvent(xoffset, yoffset));
    }
}
