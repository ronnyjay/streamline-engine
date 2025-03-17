#include "core/application.hpp"

#include <cstdlib>

using namespace engine;

Application::Application(int width, int height, const char *title)
{
    // clang-format off
    m_window           = new Window(width, height, title); 
    m_renderer         = new Renderer(width, height);
    m_sceneManager     = new SceneManager;
    m_inputManager     = new InputManager;
    m_resourceManager  = new ResourceManager;
    // clang-format on

    m_window->setEventCallback(this, &Application::onEvent);
}

void Application::run()
{
    m_renderer->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    m_renderer->enableDepth(true);
    m_renderer->enableVsync(true);

    double currentTime;
    double lastTime;
    double elapsedTime;

    double renderTimeStep = 1.0 / 60.0;
    double renderAccumulator = 0.0;

    double simulationTimeStep = 1.0 / 60.0;
    double simulationAccumulator = 0.0;

    lastTime = currentTime = glfwGetTime();

    while (m_window->isOpen())
    {
        elapsedTime = (currentTime = glfwGetTime()) - lastTime;

        simulationAccumulator += elapsedTime;
        while (simulationAccumulator >= simulationTimeStep)
        {
            m_sceneManager->currentScene()->tick(simulationTimeStep);
            simulationAccumulator -= simulationTimeStep;
        }

        renderAccumulator += elapsedTime;
        while (renderAccumulator >= renderTimeStep)
        {
            m_renderer->begin(m_sceneManager->currentScene());
            renderAccumulator -= renderTimeStep;
        }

        m_window->pollEvents();
        m_window->swapBuffers();

        lastTime = currentTime;
    }
}

void Application::onEvent(event &&e)
{
    m_inputManager->onEvent(e);
}

bool Application::onKeyPress(key_press_event &e)
{
    return true;
}

bool Application::onWindowResize(window_resize_event &e)
{
    return true;
}
