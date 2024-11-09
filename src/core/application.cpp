#include "application.hpp"

using namespace engine;

Application::Application()
{
    m_window = Window::create(800, 600, "Streamline Engine");

    m_renderer = new Renderer();
    m_display_manager = new DisplayManager(m_window);

    m_window->set_event_callback(this, &Application::on_event);
}

void Application::run()
{
    while (m_window->is_open())
    {
        glfwPollEvents();

        if (glfwGetKey(*m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            m_window->close();
        }

        m_window->swap_buffers();
    }
}

void Application::on_event(Event &&e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowResizeEvent>(this, &Application::on_window_resize);
}

bool Application::on_window_resize(WindowResizeEvent &e)
{
    m_renderer->OnViewportResize(e.width, e.height);

    return true;
}

Application::~Application()
{
    if (m_display_manager)
    {
        delete m_display_manager;
        m_display_manager = nullptr;
    }

    if (m_renderer)
    {
        delete m_renderer;
        m_renderer = nullptr;
    }

    if (m_window)
    {
        delete m_window;
        m_window = nullptr;
    }
}