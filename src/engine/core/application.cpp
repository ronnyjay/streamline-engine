#include "application.hpp"

using namespace engine;

Application::Application()
    : m_window(800, 600, "Streamline Engine")
{
    m_window.on<WindowResizedEvent>(
        [this](WindowResizedEvent &e)
        {

        });

    m_window.on<KeyPressedEvent>(
        [this](KeyPressedEvent &e)
        {

        });

    m_window.on<MousePressedEvent>(
        [this](MousePressedEvent &e)
        {

        });

    m_window.on<MouseMovedEvent>(
        [this](MouseMovedEvent &e)
        {

        });

    m_window.on<MouseScrolledEvent>(
        [this](MouseScrolledEvent &e)
        {

        });
}

void Application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}
