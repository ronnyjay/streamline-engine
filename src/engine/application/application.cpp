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

    m_window.on_resize(
        [&](resize_event e)
        {
            m_framebuffer.resize(e.width(), e.height());
            g.window_size_changed(e.width(), e.height());
        });

    m_window.on_minimize([&](minimize_event e) { m_log.info(e.to_string()); });
    m_window.on_maximize([&](maximize_event e) { m_log.info(e.to_string()); });

    m_window.set_mouse_press_callback([&](int button, int action, int mods) { g.mouse_press(button, action, mods); });

    m_window.set_mouse_pos_callback(
        [&](double x, double y)
        {
            float cx, cy;
            cx = 2.0f * (x / m_framebuffer.m_width) - 1.0f;
            cy = -2.0f * (y / m_framebuffer.m_height) + 1.0f;
            g.mouse_pos(cx, cy);
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

        // m_log.info("LAG: %f", lag);
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

        if (g.should_quit())
        {
            g.quit();
            break;
        }
    }
}
