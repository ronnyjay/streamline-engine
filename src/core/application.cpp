#include "core/application.hpp"

using namespace engine;

Application::Application()
{
    // Initialize GLFW
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

    // Load Monitors
    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        mMonitors.emplace_back(Monitor(monitors[i]));
    }

    // Initialize Window
    mWindow = Window::Create(800, 600, "Streamline Engine");
}

void Application::Run()
{
    while (mWindow->IsOpen())
    {
        mWindow->SwapBuffers();
    }
}

Application::~Application()
{
    // Destroy window
    Window::Destroy(mWindow);

    // Terminate GLFW
    glfwTerminate();
}