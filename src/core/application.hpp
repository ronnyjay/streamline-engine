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
    void Run();

    /**
     * @brief
     *
     * @return Window* const
     */
    Window *const GetWindow()
    {
        return mWindow;
    }

    /**
     * @brief
     *
     * @return Renderer* const
     */
    Renderer *const GetRenderer()
    {
        return mRenderer;
    }

    /**
     * @brief
     *
     * @return DisplayManager* const
     */
    DisplayManager *const GetDisplayManager()
    {
        return mDisplayManager;
    }

    ~Application();

    Application(const Application &other) = delete;
    Application(const Application &&other) = delete;

    Application operator=(const Application &other) = delete;
    Application operator=(const Application &&other) = delete;

  private:
    Window         *mWindow;
    Renderer       *mRenderer;
    DisplayManager *mDisplayManager;

    void            OnEvent(Event &&e);

    bool            OnWindowResize(WindowResizeEvent &e);
};

} // namespace engine
