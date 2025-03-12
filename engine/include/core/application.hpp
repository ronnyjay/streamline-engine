#pragma once

#include "core/renderer.hpp"               // IWYU pragma: keep
#include "core/window.hpp"                 // IWYU pragma: keep

#include "subsystems/display_manager.hpp"  // IWYU pragma: keep
#include "subsystems/input_manager.hpp"    // IWYU pragma: keep
#include "subsystems/resource_manager.hpp" // IWYU pragma: keep
#include "subsystems/scene_manager.hpp"    // IWYU pragma: keep

namespace engine
{

class application
{
    window *m_window                     = nullptr;
    renderer *m_renderer                 = nullptr;
    input_manager *m_input_manager       = nullptr;
    resource_manager *m_resource_manager = nullptr;

  public:
    application(int width = 800, int height = 600, const char *title = "Untitled Window");

    resource_manager *const getResourceManager() const noexcept
    {
        return m_resource_manager;
    }

    renderer *const getRenderer() const noexcept
    {
        return m_renderer;
    }

    window *const getWindow() const noexcept
    {
        return m_window;
    }

    void run();

    ~application()
    {
        if (m_resource_manager)
            delete m_resource_manager;
        if (m_input_manager)
            delete m_input_manager;
        if (m_renderer)
            delete m_renderer;
        if (m_window)
            delete m_window;
    }

    application(application const &)  = delete;
    application(application const &&) = delete;

    application operator=(application const &)  = delete;
    application operator=(application const &&) = delete;

  private:
    void onEvent(event &&e);

    bool onKeyPress(key_press_event &e);
    bool onWindowResize(window_resize_event &e);
};

} // namespace engine