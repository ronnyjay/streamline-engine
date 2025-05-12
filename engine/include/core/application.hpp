#pragma once

#include "core/debug.hpp"                  // IWYU pragma: keep
#include "core/event.hpp"
#include "core/renderer.hpp"               // IWYU pragma: keep
#include "core/settings.hpp"
#include "core/singleton.hpp"              // IWYU pragma: keep
#include "core/window.hpp"                 // IWYU pragma: keep

#include "subsystems/display_manager.hpp"  // IWYU pragma: keep
#include "subsystems/input_manager.hpp"    // IWYU pragma: keep
#include "subsystems/resource_manager.hpp" // IWYU pragma: keep
#include "subsystems/scene_manager.hpp"    // IWYU pragma: keep

namespace engine
{

class Application : public Singleton<Application>
{
    // clang-format off
    Window                   *m_window          = nullptr;
    Renderer                 *m_renderer        = nullptr;
    DebugWindow              *m_debugWindow     = nullptr;
    SceneManager             *m_sceneManager    = nullptr;
    InputManager             *m_inputManager    = nullptr;
    DisplayManager           *m_displayManager  = nullptr;
    UserSettings             *m_userSettings    = nullptr;
    ResourceManager          *m_resourceManager = nullptr;
    // clang-format on

  public:
    explicit Application(int width = 800, int height = 600, const char *title = "Streamline Engine");

    [[nodiscard]] ResourceManager *getResourceManager() const noexcept
    {
        return m_resourceManager;
    }

    [[nodiscard]] DisplayManager *getDisplayManager() const noexcept
    {
        return m_displayManager;
    }

    [[nodiscard]] InputManager *getInputManager() const noexcept
    {
        return m_inputManager;
    }

    [[nodiscard]] SceneManager *getSceneManager() const noexcept
    {
        return m_sceneManager;
    }

    [[nodiscard]] Renderer *getRenderer() const noexcept
    {
        return m_renderer;
    }

    [[nodiscard]] Window *getWindow() const noexcept
    {
        return m_window;
    }

    void run();

    ~Application()
    {
        delete m_resourceManager;
        delete m_userSettings;
        delete m_displayManager;
        delete m_sceneManager;
        delete m_inputManager;
        delete m_renderer;
        delete m_window;
    }

    Application(Application const &)             = delete;
    Application(Application const &&)            = delete;

    Application &operator=(Application const &)  = delete;
    Application &operator=(Application const &&) = delete;

  private:
    void onEvent(Event &&event);
    bool onKeyPress(KeyPressEvent &event);
    bool onWindowResize(WindowResizeEvent &event);
};

} // namespace engine
