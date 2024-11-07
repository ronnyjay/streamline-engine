#include "application.hpp"

using namespace engine;

Application::Application()
{
    m_window = Window::create(800, 600, "Streamline Engine");
}

void Application::Run()
{
    while (!glfwWindowShouldClose(*m_window))
    {
        glfwPollEvents();

        if (glfwGetKey(*m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(*m_window, GL_TRUE);
        }

        glfwSwapBuffers(*m_window);
    }
}

Application::~Application()
{
    glfwTerminate();
}