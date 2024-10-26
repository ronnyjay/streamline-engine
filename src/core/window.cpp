#include "core/window.hpp"

#include <cstdlib>

using namespace engine;

Window::Window(int width, int height, const char *title)
{
    if (!(mWindow = glfwCreateWindow(width, height, title, NULL, NULL)))
    {
        std::exit(1);
    }

    glfwMakeContextCurrent(mWindow);

    glfwSetFramebufferSizeCallback(mWindow, Window::FramebufferSizeCallback);
    glfwSetWindowMaximizeCallback(mWindow, Window::WindowMaximizeCallback);
    glfwSetWindowIconifyCallback(mWindow, Window::WindowMinimizeCallback);
    glfwSetMouseButtonCallback(mWindow, Window::MouseButtonCallback);
    glfwSetCursorPosCallback(mWindow, Window::CursorPosCallback);
    glfwSetScrollCallback(mWindow, Window::ScrollCallback);
    glfwSetKeyCallback(mWindow, Window::KeyCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::exit(1);
    }

    glfwSetWindowUserPointer(mWindow, this);
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(mWindow);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(mWindow);
}

void Window::ShowMouse(bool value)
{
    if ((mShowMouse = value))
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Window::CaptureMouse(bool value)
{
    mCaptureMouse = value;
}

void Window::SetDecorated(bool value)
{
    glfwSetWindowAttrib(mWindow, GLFW_DECORATED, (mDecorated = value));
}

void Window::SetFloating(bool value)
{
    glfwSetWindowAttrib(mWindow, GLFW_FLOATING, (mFloating = value));
}

void Window::SetResizable(bool value)
{
    glfwSetWindowAttrib(mWindow, GLFW_RESIZABLE, (mResizable = value));
}

Window *Window::Create(int width, int height, const char *title)
{
    return new Window(width, height, title);
}

void Window::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
    static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow))
        ->dispatch(EventType::WindowResized, WindowResizeEvent(width, height));
}

void Window::WindowMaximizeCallback(GLFWwindow *glfwWindow, int maximize)
{
    maximize ? glfwMaximizeWindow(glfwWindow) : glfwRestoreWindow(glfwWindow);
}

void Window::WindowMinimizeCallback(GLFWwindow *glfwWindow, int minimize)
{
    minimize ? glfwIconifyWindow(glfwWindow) : glfwRestoreWindow(glfwWindow);
}

void Window::KeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (action == GLFW_RELEASE)
    {
        window->dispatch(EventType::KeyReleased, KeyReleaseEvent(key));
    }
    else
    {
        window->dispatch(EventType::KeyPressed, KeyPressEvent(key, mods, action == GLFW_REPEAT ? 1 : 0));
    }
}

void Window::MouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (action == GLFW_RELEASE)
    {
        window->dispatch(EventType::MouseButtonReleased, MouseButtonReleaseEvent(button));
    }
    else
    {
        window->dispatch(EventType::MouseButtonPressed, MouseButtonPressEvent(button, mods));
    }
}

void Window::CursorPosCallback(GLFWwindow *glfwWindow, double xPosIn, double yPosIn)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (!window->mCaptureMouse)
    {
        return;
    }

    static float lastY = window->mWidth / 2.0f;
    static float lastX = window->mHeight / 2.0f;

    if (window->mFirstMouse)
    {
        lastX               = xPosIn;
        lastY               = yPosIn;

        window->mFirstMouse = false;
    }

    float xPos    = static_cast<float>(xPosIn);
    float yPos    = static_cast<float>(yPosIn);

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX         = xPos;
    lastY         = yPos;

    window->dispatch(EventType::MouseMoved, MouseMoveEvent(xOffset, yOffset));
}

void Window::ScrollCallback(GLFWwindow *glfwWindow, double xOffset, double yOffset)
{
    static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow))
        ->dispatch(EventType::MouseScrolled, MouseScrollEvent(xOffset));
}
