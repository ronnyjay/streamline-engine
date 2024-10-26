#include "core/application.hpp"
#include "core/specification.hpp"

using namespace engine;

Application::Application(Specification &&specification)
    : mSpecification(specification)
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

    // Initialize Window
    mWindow = Window::Create(800, 600, "Streamline Engine");

    // Load Monitors
    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        mMonitors.emplace_back(Monitor(monitors[i]));
    }

    // Pass to specification
    mSpecification.OnInit(this);
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
    // Pass to specification
    mSpecification.OnExit(this);

    // Destroy window
    Window::Destroy(mWindow);

    // Terminate GLFW
    glfwTerminate();
}