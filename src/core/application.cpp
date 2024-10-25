#include "core/application.hpp"

using namespace engine;

Application::Application()
    : m_window(800, 600, "Streamline Engine")
{
    m_window.on<WindowResizeEvent>(
        [this](WindowResizeEvent &e) {

        });

    m_window.on<KeyPressEvent>(
        [this](KeyPressEvent &e)
        {
            if (e.key == GLFW_KEY_ESCAPE)
            {
                glfwSetWindowShouldClose(m_window, true);
            }
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