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
    mWindow = new Window(800, 600, "Streamline Engine");
}

void Application::Run()
{
}

Application::~Application()
{
    // Pass to specification
    mSpecification.OnExit(this);

    // Destroy window
    delete mWindow;
    mWindow = nullptr;

    // Terminate GLFW
    glfwTerminate();
}