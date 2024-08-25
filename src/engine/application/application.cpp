#include "application.hpp"

#include <engine/glfw3.h>
#include <libstreamline/debug/logger.hpp>
#include <libstreamline/json/json.hpp>

#include "engine/shader/shader.hpp"
#include "window.hpp"

using namespace engine;

void application::initialize(game &g)
{
    std::filesystem::path config_path("config/video.json");
    window_config window_cfg;

    if (!std::filesystem::exists(config_path))
    {
        m_log.info("No config found. Creating default.");
        window_cfg.export_to_file();
    }
    else
    {
        window_cfg.load(json::parse(config_path));
    }

    m_window.set_framebuffer_size_callback(
        [&](int w, int h)
        {
            glViewport(0, 0, w, h);
            m_framebuffer.resize(w, h);
            g.window_size_changed(w, h);
        });

    m_window.initialize(window_cfg);
}

void application::run(game &g)
{
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    double previous = glfwGetTime();
    double lag = 0.0;

    while (!glfwWindowShouldClose(m_window.glfw_window()))
    {
        glClearColor(0.0f, 0.0f, 0.7f, 1.0f);
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

        // render to our framebuffer
        m_framebuffer.bind();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glClearColor(0.30f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g.render(lag / SECONDS_PER_UPDATE);

        // done rendering to our framebuffer
        m_framebuffer.unbind();

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        // render the framebuffer to the default framebuffer
        m_framebuffer.render();

        glfwSwapBuffers(m_window.glfw_window());
    }
}
