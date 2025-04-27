#include "core/application.hpp"
#include "core/event.hpp"
#include "core/settings.hpp"
#include "core/window.hpp"
#include "subsystems/display_manager.hpp"
#include "subsystems/settings_manager.hpp"

#include <bits/this_thread_sleep.h>
#include <cmath>
#include <cstdlib>

using namespace engine;

Application::Application(int width, int height, const char *title)
{
    m_window          = new Window(width, height, title);
    m_renderer        = new Renderer(width, height);
    m_debugWindow     = new DebugWindow;
    m_sceneManager    = new SceneManager;
    m_inputManager    = new InputManager;
    m_displayManager  = new DisplayManager;
    m_settingsManager = new SettingsManager;
    m_userSettings    = new UserSettings;
    m_resourceManager = new ResourceManager;

    m_window->setEventCallback(this, &Application::onEvent);
}

void Application::run()
{
    m_renderer->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    m_renderer->enableDepth(true);
    m_renderer->setVerticalSync(true);

    double currentTime;
    double lastTime;
    double elapsedTime;

    double renderTimeStep        = 1.0 / 240.0;
    double renderAccumulator     = 0.0;
    double simulationTimeStep    = 1.0 / 240.0;
    double simulationAccumulator = 0.0;

    lastTime = currentTime = glfwGetTime();

    // TODO: Simulation, Rendering should be moved to seperate threads
    //
    // With this setup, rendering is bottlenecked by the speed of the simulation
    // i.e., If simulating scene at 30FPS, rendering will now also be ~30FPS, which is not desired
    //
    // Basically, this whole loop must be reworked at some point
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
            m_debugWindow->draw();
            renderAccumulator -= renderTimeStep;
        }

        m_window->swapBuffers();
        m_window->pollEvents();

        lastTime = currentTime;
    }
}

void Application::onEvent(Event &&e)
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<WindowResizeEvent>(this, &Application::onWindowResize);
    dispatcher.dispatch<KeyPressEvent>(this, &Application::onKeyPress);

    if (!e.b_isHandled)
    {
        m_inputManager->onEvent(e);
    }
}

bool Application::onKeyPress(KeyPressEvent &e)
{
    if (Key(e.key) == Key::GraveAccent)
    {
        if (Modifier(e.mods) == Modifier::Shift)
        {
            m_window->flags.b_mouseVisible = !m_window->flags.b_mouseVisible;

            if (m_window->flags.b_mouseVisible)
            {
                m_window->showCursor();
            }
            else
            {
                m_window->hideCursor();
            }

            m_window->flags.b_mouseEntered = true;
        }
        else
        {
            if (m_debugWindow->b_showMetrics)
            {
                m_debugWindow->b_showMetrics = false;
            }
            else
            {
                m_debugWindow->b_showWindow = !m_debugWindow->b_showWindow;

                if (m_debugWindow->b_showWindow)
                {
                    m_inputManager->b_captureMouseInput = false;

                    if (!m_window->flags.b_mouseVisible)
                    {
                        m_window->showCursor();
                    }
                }
                else
                {
                    m_inputManager->b_captureMouseInput = true;

                    if (!m_window->flags.b_mouseVisible)
                    {
                        m_window->hideCursor();
                    }
                }

                m_window->flags.b_mouseEntered = true;
            }
        }

        return true;
    }

    return false;
}

bool Application::onWindowResize(WindowResizeEvent &e)
{
    m_sceneManager->currentScene()->onWindowResize(e.width, e.height);

    return true;
}
