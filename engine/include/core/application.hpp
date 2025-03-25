#pragma once

#include "core/debug.hpp"                  // IWYU pragma: keep
#include "core/renderer.hpp"               // IWYU pragma: keep
#include "core/singleton.hpp"              // IWYU pragma: keep
#include "core/window.hpp"                 // IWYU pragma: keep

#include "subsystems/display_manager.hpp"  // IWYU pragma: keep
#include "subsystems/input_manager.hpp"    // IWYU pragma: keep
#include "subsystems/resource_manager.hpp" // IWYU pragma: keep
#include "subsystems/scene_manager.hpp"    // IWYU pragma: keep
#include <cstdint>

namespace engine
{

class Application : public Singleton<Application>
{
    // clang-format off
    static constexpr uint32_t WINDOW_WIDTH      = 800;
    static constexpr uint32_t WINDOW_HEIGHT     = 600;

    Window                   *m_window          = nullptr;
    Renderer                 *m_renderer        = nullptr;
    DebugWindow              *m_debugWindow     = nullptr;
    SceneManager             *m_sceneManager    = nullptr;
    InputManager             *m_inputManager    = nullptr;
    ResourceManager          *m_resourceManager = nullptr;
    // clang-format on

  public:
    explicit Application(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, const char *title = "Streamline Engine");

    [[nodiscard]] ResourceManager *getResourceManager() const noexcept
    {
        return m_resourceManager;
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
        delete m_sceneManager;
        delete m_inputManager;
        delete m_renderer;
        delete m_window;
    }

    Application(Application const &)  = delete;
    Application(Application const &&) = delete;

    Application &operator=(Application const &)  = delete;
    Application &operator=(Application const &&) = delete;

  private:
    void onEvent(Event &&event);
    bool onKeyPress(KeyPressEvent &event);
    bool onWindowResize(WindowResizeEvent &event);
};

} // namespace engine
