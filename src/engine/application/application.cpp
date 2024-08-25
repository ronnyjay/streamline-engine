#include "application.hpp"

#include <GLFW/glfw3.h>
#include <libstreamline/debug/logger.hpp>
#include <libstreamline/json/json.hpp>

#include "window.hpp"

using namespace engine;

void application::initialize()
{
    std::filesystem::path config_path("config/video.json");
    window_config window_cfg;

    if (!std::filesystem::exists(config_path))
    {
        m_log.info("No config found. Creating default.\n");
        window_cfg.export_to_file();
    }
    else
    {
        window_cfg.load(json::parse(config_path));
    }

    m_window.initialize(window_cfg);
}

void application::run()
{
    glfwSwapInterval(m_window.is_vsync_enabled());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glViewport(0, 0, m_window.width(), m_window.height());

    double previous = glfwGetTime();
    double lag = 0.0;

    while (!glfwWindowShouldClose(m_window.glfw_window()))
    {
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        glfwPollEvents();

        while (lag >= SECONDS_PER_UPDATE)
        {
            m_game.update(SECONDS_PER_UPDATE);
            lag -= SECONDS_PER_UPDATE;
        }

        // render
        m_game.render(lag / SECONDS_PER_UPDATE);
        glfwSwapBuffers(m_window.glfw_window());
    }
}
