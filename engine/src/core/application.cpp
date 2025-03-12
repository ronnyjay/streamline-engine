#include "core/application.hpp"

#include <cstdlib>

using namespace engine;

application::application(int width, int height, const char *title)
{
    m_window           = new window(width, height, title);
    m_renderer         = new renderer;
    m_input_manager    = new input_manager;
    m_resource_manager = new resource_manager;
}

void application::run()
{
    m_renderer->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    m_renderer->enableDepth(true);
    m_renderer->enableVsync(true);

    while (m_window->isOpen())
    {
        m_window->pollEvents();

        m_renderer->clear();

        m_window->swapBuffers();
    }
}

void application::onEvent(event &&e)
{
    event_dispatcher dispatcher(e);

    dispatcher.dispatch<key_press_event>(this, &application::onKeyPress);
    dispatcher.dispatch<window_resize_event>(this, &application::onWindowResize);
}

bool application::onKeyPress(key_press_event &e)
{
    return true;
}

bool application::onWindowResize(window_resize_event &e)
{
    return true;
}
