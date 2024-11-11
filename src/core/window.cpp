#include <cassert>
#include <core/window.hpp>
#include <cstring>

using namespace engine;

Window *Window::Create(int width, int height, const char *title)
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

    // Leave on for normal window behavior
    // Disabling allows for repositioning with i3, sway
    // Must be done before window is created
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

void Window::Close()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(mWindow);
}

bool Window::IsFocused() const
{
    return glfwGetWindowAttrib(mWindow, GLFW_FOCUSED);
}

bool Window::IsDecorated() const
{
    return glfwGetWindowAttrib(mWindow, GLFW_DECORATED);
}

bool Window::IsFloating() const
{
    return glfwGetWindowAttrib(mWindow, GLFW_FLOATING);
}

bool Window::IsResizable() const
{
    return glfwGetWindowAttrib(mWindow, GLFW_RESIZABLE);
}

Vector2i Window::GetPositionInScreen() const
{
    Vector2i position;

    glfwGetWindowPos(mWindow, &position.x, &position.y);

    return position;
}

Vector2i Window::GetSizeInScreen() const
{
    Vector2i size;

    glfwGetWindowSize(mWindow, &size.x, &size.y);

    return size;
}

void Window::MoveTo(int x, int y)
{
    if (glfwGetWindowMonitor(mWindow))
    {
        return;
    }

    mLastPos.x = x;
    mLastPos.y = y;

    glfwSetWindowPos(mWindow, x, y);
}

void Window::Resize(int w, int h)
{
    if (glfwGetWindowMonitor(mWindow))
    {
        return;
    }

    mLastSize.x = w;
    mLastSize.y = h;

    glfwSetWindowSize(mWindow, w, h);
}

void Window::SetWindowMode(WindowMode m)
{
    if (mWindowMode == WindowMode::Windowed)
    {
        glfwGetWindowPos(mWindow, &mLastPos.x, &mLastPos.y);
        glfwGetWindowSize(mWindow, &mLastSize.x, &mLastSize.y);
    }

    if (m == WindowMode::Windowed)
    {
        if (!glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_TRUE);
        }

        if (glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GLFW_FALSE);
        }

        glfwSetWindowMonitor(mWindow, nullptr, mLastPos.x, mLastPos.y, mLastSize.x, mLastSize.y, GLFW_DONT_CARE);

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

        bool overlap_x = (mLastPos.x >= x && mLastPos.x < x + w);
        bool overlap_y = (mLastPos.y >= y && mLastPos.y < y + h);

        if (overlap_x && overlap_y)
        {
            monitor = monitors[i];
            break;
        }
    }

    if (WindowMode(m) == WindowMode::Fullscreen)
    {
        glfwSetWindowMonitor(mWindow, monitor, 0, 0, w, h, GLFW_DONT_CARE);
    }

    else if (WindowMode(m) == WindowMode::FullscreenBorderless)
    {
        if (glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
        {
            glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GLFW_FALSE);
        }

        if (!glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
        {
            glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GLFW_TRUE);
        }

        glfwSetWindowMonitor(mWindow, nullptr, x, y, w, h, GLFW_DONT_CARE);
    }

    mWindowMode = m;
}

Window::~Window()
{
    if (mWindow)
    {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
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
