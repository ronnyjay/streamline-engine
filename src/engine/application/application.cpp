#include "application.hpp"

#include <engine/glfw3.h>
#include <libstreamline/debug/logger.hpp>
#include <libstreamline/json/json.hpp>

#include "window.hpp"

using namespace engine;

void application::initialize(game &g)
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

    m_window.set_framebuffer_size_callback(
        std::bind(&game::window_size_changed, &g, std::placeholders::_1, std::placeholders::_2));

    m_window.initialize(window_cfg);
}

void application::run(game &g)
{
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
            g.update(SECONDS_PER_UPDATE);
            lag -= SECONDS_PER_UPDATE;
        }

        // render
        g.render(lag / SECONDS_PER_UPDATE);
        glfwSwapBuffers(m_window.glfw_window());
    }
}
