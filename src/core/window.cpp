#include "window.hpp"
#include <cstring>

using namespace engine;

Window::Window(int width, int height, const char *title)
{
    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        // TODO: Safely terminate
    }

    glfwGetWindowPos(mWindow, &mX, &mY);
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
}

void Window::SetWindowPosition(int x, int y)
{
    glfwSetWindowPos(mWindow, x, y);
    glfwGetWindowPos(mWindow, &mX, &mY);
}

void Window::SetWindowSize(int width, int height)
{
    glfwSetWindowSize(mWindow, width, height);
    glfwGetWindowSize(mWindow, &mWidth, &mHeight);
}

void Window::SetFullscreen()
{
    GLFWmonitor *monitor = mPreferredMonitor;

    if (!monitor)
    {
        monitor = GetMonitor();
    }

    int monitorX, monitorY;
    int monitorWidth, monitorHeight;
    glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

    glfwSetWindowMonitor(mWindow, NULL, monitorX, monitorY, monitorWidth, monitorHeight, GLFW_DONT_CARE);
    glfwSetWindowMonitor(mWindow, monitor, 0, 0, monitorWidth, monitorHeight, GLFW_DONT_CARE);
}

void Window::SetWindowed()
{
    if (glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
    {
        glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GL_FALSE);
    }

    if (!glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
    {
        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GL_TRUE);
    }

    glfwSetWindowMonitor(mWindow, NULL, mX, mY, mWidth, mHeight, GLFW_DONT_CARE);
}

void Window::SetBorderless()
{
    GLFWmonitor *monitor = mPreferredMonitor;

    if (!monitor)
    {
        monitor = GetMonitor();
    }

    int monitorX, monitorY;
    int monitorWidth, monitorHeight;
    glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

    if (glfwGetWindowAttrib(mWindow, GLFW_DECORATED))
    {
        glfwSetWindowAttrib(mWindow, GLFW_DECORATED, GL_FALSE);
    }

    if (!glfwGetWindowAttrib(mWindow, GLFW_FLOATING))
    {
        glfwSetWindowAttrib(mWindow, GLFW_FLOATING, GL_TRUE);
    }

    glfwSetWindowMonitor(mWindow, nullptr, monitorX, monitorY, monitorWidth, monitorHeight, GLFW_DONT_CARE);
}

void Window::SetMonitor(const Monitor &preferredMonitor)
{
    if (auto *monitor = (GLFWmonitor *)const_cast<Monitor &>(preferredMonitor))
    {

        mPreferredMonitor = monitor;
    }
}

Window::~Window()
{
    if (mWindow)
    {
        glfwDestroyWindow(mWindow);
    }
}