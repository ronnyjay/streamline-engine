#include "window.hpp"
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

Vector2i Window::GetPositionInScreen() const
{
    Vector2i position;

    glfwGetWindowPos(mBaseWindow, &position.x, &position.y);

    return position;
}

Vector2i Window::GetSizeInScreen() const
{
    Vector2i size;

    glfwGetWindowSize(mBaseWindow, &size.x, &size.y);

    return size;
}

void Window::MoveTo(int x, int y)
{
    if (glfwGetWindowMonitor(mBaseWindow))
    {
        return;
    }

    mLastPosition.x = x;
    mLastPosition.y = y;

    glfwSetWindowPos(mBaseWindow, x, y);
}

void Window::Resize(int w, int h)
{
    if (glfwGetWindowMonitor(mBaseWindow))
    {
        return;
    }

    mLastSize.x = w;
    mLastSize.y = h;

    glfwSetWindowSize(mBaseWindow, w, h);
}

void Window::SetWindowMode(WindowMode m)
{
    if (mWindowMode == WindowMode::Windowed)
    {
        glfwGetWindowPos(mBaseWindow, &mLastPosition.x, &mLastPosition.y);
        glfwGetWindowSize(mBaseWindow, &mLastSize.x, &mLastSize.y);
    }

    if (m == WindowMode::Windowed)
    {
        if (!glfwGetWindowAttrib(mBaseWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mBaseWindow, GLFW_DECORATED, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(mBaseWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mBaseWindow, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(
            mBaseWindow, nullptr, mLastPosition.x, mLastPosition.y, mLastSize.x, mLastSize.y, GLFW_DONT_CARE);

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

        bool overlap_x = (mLastPosition.x >= x && mLastPosition.x < x + w);
        bool overlap_y = (mLastPosition.y >= y && mLastPosition.y < y + h);

        if (overlap_x && overlap_y)
        {
            monitor = monitors[i];
            break;
        }
    }

    if (WindowMode(m) == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(mBaseWindow, nullptr, x, y, w, h, GLFW_DONT_CARE);
        glfwSetWindowMonitor(mBaseWindow, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    else if (WindowMode(m) == WindowMode::Borderless)
    {
        if (!glfwGetWindowAttrib(mBaseWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mBaseWindow, GLFW_FLOATING, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(mBaseWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mBaseWindow, GLFW_DECORATED, GLFW_FALSE);
        }

        glfwSetWindowMonitor(mBaseWindow, nullptr, x, y, w, h, GLFW_DONT_CARE);
    }

    mWindowMode = m;
}

Window::~Window()
{
    if (mBaseWindow)
    {
        glfwDestroyWindow(mBaseWindow);
        mBaseWindow = nullptr;
    }

    glfwTerminate();
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->mEventCallback)
    {
        w->mEventCallback(WindowResizeEvent(width, height));
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

    if (w->mEventCallback)
    {
        if (action == GLFW_RELEASE)
        {
            w->mEventCallback(KeyReleaseEvent(key));
        }
        else
        {
            w->mEventCallback(KeyPressEvent(key, mods, action == GLFW_REPEAT));
        }
    }
}

void Window::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->mEventCallback)
    {
        if (action == GLFW_PRESS)
        {
            w->mEventCallback(MouseButtonPressEvent(button));
        }
        else
        {
            w->mEventCallback(MouseButtonReleaseEvent(button));
        }
    }
}

void Window::CursorPosCallback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->mEventCallback)
    {
        w->mEventCallback(MouseMoveEvent(x, y));
    }
}

void Window::ScrollCallback(GLFWwindow *window, double x, double y)
{
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (w->mEventCallback)
    {
        w->mEventCallback(MouseScrollEvent(x, y));
    }
}
