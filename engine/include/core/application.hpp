#pragma once

#include "core/renderer.hpp"               // IWYU pragma: keep
#include "core/window.hpp"                 // IWYU pragma: keep

#include "subsystems/display_manager.hpp"  // IWYU pragma: keep
#include "subsystems/input_manager.hpp"    // IWYU pragma: keep
#include "subsystems/resource_manager.hpp" // IWYU pragma: keep
#include "subsystems/scene_manager.hpp"    // IWYU pragma: keep

namespace engine
{

class Application
{
    Window          *m_window = nullptr;
    Renderer        *m_renderer = nullptr;
    SceneManager    *m_sceneManager = nullptr;
    InputManager    *m_inputManager = nullptr;
    ResourceManager *m_resourceManager = nullptr;

  public:
    Application(int width = 800, int height = 600, const char *title = "Untitled Window");

    ResourceManager *const getResourceManager() const noexcept
    {
        return m_resourceManager;
    }

    InputManager *const getInputManager() const noexcept
    {
        return m_inputManager;
    }

    SceneManager *const getSceneManager() const noexcept
    {
        return m_sceneManager;
    }

    Renderer *const getRenderer() const noexcept
    {
        return m_renderer;
    }

    Window *const getWindow() const noexcept
    {
        return m_window;
    }

    void run();

    ~Application()
    {
        if (m_resourceManager)
            delete m_resourceManager;
        if (m_sceneManager)
            delete m_sceneManager;
        if (m_inputManager)
            delete m_inputManager;
        if (m_renderer)
            delete m_renderer;
        if (m_window)
            delete m_window;
    }

    Application(Application const &) = delete;
    Application(Application const &&) = delete;

    Application operator=(Application const &) = delete;
    Application operator=(Application const &&) = delete;

  private:
    void onEvent(event &&e);

    bool onKeyPress(key_press_event &e);
    bool onWindowResize(window_resize_event &e);
};

} // namespace engine