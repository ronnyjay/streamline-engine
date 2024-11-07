#include "application.hpp"

using namespace engine;

Application::Application()
{
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