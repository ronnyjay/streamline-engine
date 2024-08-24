#include "application.hpp"
#include "window.hpp"

#include <libstreamline/config/config.hpp>
#include <libstreamline/debug/logger.hpp>

application *application::ref = nullptr;

application::application()
{
    // load configuration
    m_config.load(json::parse("config/video.json"));

    // initialize window
    m_window.initialize(m_config);
}

void application::run()
{
    glfwSwapInterval(m_config.vsync);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glViewport(0, 0, m_window.width(), m_window.height());

    while (!glfwWindowShouldClose(m_window.glfw_window()))
    {
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_window.glfw_window());
        glfwPollEvents();
    }
}
