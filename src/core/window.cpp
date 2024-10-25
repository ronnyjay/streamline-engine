#include "core/window.hpp"

using namespace engine;

Window::Window()
{
    if (!glfwInit())
    {
    }
}

void Window::create(int width, int height, const char *title)
{
}
