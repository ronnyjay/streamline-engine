#pragma once

#include "displaymanager.hpp"
#include "renderer/renderer.hpp"
#include "window.hpp"

namespace engine
{

class Application
{
  public:
    /**
     * @brief
     *
     */
    Application();

    /**
     * @brief
     *
     */
    void run();

    /**
     * @brief
     *
     * @return Window* const
     */
    Window *const window()
    {
        return m_window;
    }

    /**
     * @brief
     *
     * @return Renderer* const
     */
    Renderer *const renderer()
    {
        return m_renderer;
    }

    /**
     * @brief
     *
     * @return DisplayManager* const
     */
    DisplayManager *const display_manager()
    {
        return m_display_manager;
    }

    ~Application();

    Application(const Application &other) = delete;
    Application(const Application &&other) = delete;

    Application operator=(const Application &other) = delete;
    Application operator=(const Application &&other) = delete;

  private:
    Window         *m_window;
    Renderer       *m_renderer;
    DisplayManager *m_display_manager;

    void            on_event(Event &&e);

    bool            on_window_resize(WindowResizeEvent &e);
};

} // namespace engine
