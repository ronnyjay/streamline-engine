#include "core/application.hpp"

#include <cstdlib>

using namespace engine;

Application::Application(int width, int height, const char *title)
{
    // clang-format off
    m_window           = new Window(width, height, title);
    
    m_renderer         = new Renderer;
    m_scene_manager    = new SceneManager;
    m_input_manager    = new InputManager;
    m_resource_manager = new ResourceManager;

    m_scene = new scene;    

    m_window->setEventCallback(this, &Application::onEvent);
    // clang-format on
}

void Application::run()
{
    auto e1 = m_scene->create();
    auto e2 = m_scene->create();

    m_scene->emplace<Renderable>(e1, ResourceManager::getInstance().getModel("../assets/objects/cube/cube.obj"));
    auto &t       = m_scene->emplace<Transform>(e1);
    t.translation = vec3(0.0f, 0.0f, 0.0f);

    m_scene->emplace<PlayerInput>(e2);
    m_scene->emplace<Move>(e2);
    m_scene->emplace<Look>(e2);
    m_scene->emplace<PlayerController>(e2);
    auto &c       = m_scene->emplace<Camera>(e2, Projection::Perspective);
    c.b_isPrimary = true;
    m_scene->emplace<Transform>(e2);

    m_renderer->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // todo: retina display scaling
    m_renderer->setViewport(0, 0, 1600, 1200);

    m_renderer->enableDepth(true);
    m_renderer->enableVsync(true);

    while (m_window->isOpen())
    {
        m_window->pollEvents();

        m_renderer->clear();
        m_scene->tick(1);
        m_scene->draw();

        m_window->swapBuffers();
    }
}

void Application::onEvent(event &&e)
{
    event_dispatcher dispatcher(e);
    dispatcher.dispatch<mouse_move_event>([](mouse_move_event &e) -> bool
                                          { return InputManager::getInstance().onMouseMove(e); });

    dispatcher.dispatch<key_press_event>(this, &Application::onKeyPress);
    dispatcher.dispatch<window_resize_event>(this, &Application::onWindowResize);
}

bool Application::onKeyPress(key_press_event &e)
{
    return true;
}

bool Application::onWindowResize(window_resize_event &e)
{
    return true;
}
