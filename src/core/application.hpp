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
        return mWindow.get();
    }

    /**
     * @brief
     *
     * @return Renderer* const
     */
    Renderer *const GetRenderer()
    {
        return mRenderer.get();
    }

    /**
     * @brief
     *
     * @return DisplayManager* const
     */
    DisplayManager *const GetDisplayManager()
    {
        return mDisplayManager.get();
    }

    ~Application();

    Application(const Application &other)            = delete;
    Application(const Application &&other)           = delete;

    Application operator=(const Application &other)  = delete;
    Application operator=(const Application &&other) = delete;

  private:
    std::unique_ptr<Window>         mWindow;
    std::unique_ptr<Renderer>       mRenderer;
    std::unique_ptr<DisplayManager> mDisplayManager;
};

} // namespace engine
