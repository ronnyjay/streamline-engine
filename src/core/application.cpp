#include "application.hpp"

using namespace engine;

std::unique_ptr<Application> Application::kInstance = nullptr;

Application::Application()
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

    mWindow = Window::create(800, 600, "Streamline Engine");
}

void Application::Run()
{
    while (!glfwWindowShouldClose(*mWindow))
    {
        glfwPollEvents();

        if (glfwGetKey(*mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(*mWindow, GL_TRUE);
        }

        glfwSwapBuffers(*mWindow);
    }
}

Application::~Application()
{
    glfwTerminate();
}