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
    glfwSetCursorPosCallback(mWindow, Window::CursorCallback);
    glfwSetScrollCallback(mWindow, Window::ScrollCallback);
    glfwSetKeyCallback(mWindow, Window::KeyCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::exit(1);
    }

    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
}

void Window::FramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
}

void Window::WindowMaximizeCallback(GLFWwindow *glfwWindow, int maximize)
{
}

void Window::WindowMinimizeCallback(GLFWwindow *glfwWindow, int minimize)
{
}

void Window::CursorCallback(GLFWwindow *glfwWindow, double xPosIn, double yPosIn)
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

    // TODO: Dispatch event with xOffset, yOffset
}

void Window::ScrollCallback(GLFWwindow *window, double x, double y)
{
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
}
