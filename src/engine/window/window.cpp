#include <engine/window/window.hpp>

using namespace engine;

#include <engine/window/window.hpp>
#include <stdexcept>

using namespace engine;

Window::Window() : m_width(800), m_height(600), m_title("Untitled Window")
{
    initialize();
}

Window::Window(int width, int height, const char *title) : m_width(width), m_height(height), m_title(title)
{
    initialize();
}

void Window::initialize()
{
    m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

    if (m_window == NULL)
    {
        throw std::runtime_error("Failed to create GLFW Window");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to intialize GLAD");
    }
}

void Window::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void Window::minimize(int minimize)
{
    if (minimize)
    {
        glfwIconifyWindow(m_window);
    }
    else
    {
        glfwRestoreWindow(m_window);
    }

    glfwGetWindowSize(m_window, &m_width, &m_height);
}

void Window::maximize(int maximize)
{
    if (maximize)
    {
        glfwMaximizeWindow(m_window);
    }
    else
    {
        glfwRestoreWindow(m_window);
    }

    glfwGetWindowSize(m_window, &m_width, &m_height);
}

void Window::close()
{
    glfwSetWindowShouldClose(m_window, true);
}

Window::~Window()
{
    close();
}
