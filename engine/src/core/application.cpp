#include "core/application.hpp"

#include <cstdlib>

using namespace engine;

Application::Application(int width, int height, const char *title)
{
    m_window          = new Window(width, height, title);
    m_renderer        = new Renderer(width, height);
    m_debugWindow     = new DebugWindow;
    m_sceneManager    = new SceneManager;
    m_inputManager    = new InputManager;
    m_resourceManager = new ResourceManager;

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

    double renderTimeStep    = 1.0 / 240.0;
    double renderAccumulator = 0.0;

    double simulationTimeStep    = 1.0 / 240.0;
    double simulationAccumulator = 0.0;

    lastTime = currentTime = glfwGetTime();

    while (m_window->isOpen())
    {
        elapsedTime = (currentTime = glfwGetTime()) - lastTime;

        m_window->pollEvents();

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

        m_debugWindow->draw();

        m_window->swapBuffers();

        lastTime = currentTime;
    }
}

void Application::onEvent(event &&e)
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<key_press_event>(this, &Application::onKeyPress);

    if (!e.b_isHandled)
    {
        m_inputManager->onEvent(e);
    }
}

bool Application::onKeyPress(key_press_event &e)
{
    if (Key(e.key) == Key::GraveAccent)
    {
        if (Modifier(e.mods) == Modifier::Shift)
        {
            m_window->toggleCursor();
        }
        else
        {
            if (m_debugWindow->showDebugMetrics)
            {
                m_debugWindow->showDebugMetrics = false;
            }
            else
            {
                m_debugWindow->showDebugWindow = !m_debugWindow->showDebugWindow;

                if (m_debugWindow->showDebugWindow)
                {
                    m_inputManager->captureMouseInput = false;

                    if (!m_window->shouldShowCursor())
                    {
                        m_window->showCursor();
                    }
                }
                else
                {
                    m_inputManager->captureMouseInput = true;

                    if (!m_window->shouldShowCursor())
                    {
                        m_window->hideCursor();
                    }
                }
            }
        }

        return true;
    }

    return false;
}

bool Application::onWindowResize(window_resize_event &e)
{
    return true;
}
