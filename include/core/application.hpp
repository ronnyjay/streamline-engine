#pragma once

#include "managers/audio_manager.hpp"    // IWYU pragma: keep
#include "managers/display_manager.hpp"  // IWYU pragma: keep
#include "managers/resource_manager.hpp" // IWYU pragma: keep

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
     * @brief Retrieves a pointer to the DisplayManager
     *
     * @return DisplayManager*
     */
    DisplayManager *GetDisplayManager()
    {
        return mDisplayManager.get();
    }

    ~Application();

    Application(const Application &other) = delete;
    Application(const Application &&other) = delete;

    Application operator=(const Application &other) = delete;
    Application operator=(const Application &&other) = delete;

  private:
    Window                         *mWindow;
    Renderer                       *mRenderer;

    std::unique_ptr<DisplayManager> mDisplayManager;

    void                            OnEvent(Event &&e);

    bool                            OnWindowResize(WindowResizeEvent &e);
};

} // namespace engine
