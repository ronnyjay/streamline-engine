#include "core/window.hpp"

#include <cstdlib>

using namespace engine;

Window::Window(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (!(mWindow = glfwCreateWindow(width, height, title, NULL, NULL)))
    {
        std::exit(1);
    }

    glfwMakeContextCurrent(mWindow);

    glfwSetWindowUserPointer(mWindow, this);

    glfwSetFramebufferSizeCallback(mWindow, Window::FramebufferSizeCallback);
    glfwSetWindowIconifyCallback(mWindow, Window::WindowMinimizeCallback);
    glfwSetWindowMaximizeCallback(mWindow, Window::WindowMaximizeCallback);
    glfwSetKeyCallback(mWindow, Window::KeyCallback);
    glfwSetMouseButtonCallback(mWindow, Window::MouseCallback);
    glfwSetScrollCallback(mWindow, Window::ScrollCallback);
    glfwSetCursorPosCallback(mWindow, Window::CursorPosCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::exit(1);
    }

    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
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
    // TODO:
    // KeyPressed
    // KeyReleased
}

void Window::MouseCallback(GLFWwindow *glfwWindow, int button, int action, int mods)
{
    // TODO:
    // MouseButtonPressed
    // MouseButtonReleased
}

void Window::ScrollCallback(GLFWwindow *glfwWindow, double x, double y)
{
    // TODO:
    // MouseScroll
}

void Window::CursorPosCallback(GLFWwindow *glfwWindow, double xPosIn, double yPosIn)
{
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    if (!window->bCaptureMouse)
    {
        return;
    }

    static float lastY = window->mWidth / 2.0f;
    static float lastX = window->mHeight / 2.0f;

    if (window->bFirstMouse)
    {
        lastX = xPosIn;
        lastY = yPosIn;

        window->bFirstMouse = false;
    }

    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    window->dispatch(EventType::MouseMoved, MouseMoveEvent(xOffset, yOffset));
}
