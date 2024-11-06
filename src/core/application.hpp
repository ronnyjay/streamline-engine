#pragma once

#include "window.hpp"

namespace engine
{

class Application
{
  public:
    Application();

    void          Run();

    Window *const GetTopLevelWindow()
    {
        return mWindow.get();
    }

    ~Application();

    Application(const Application &other)            = delete;
    Application(const Application &&other)           = delete;

    Application operator=(const Application &other)  = delete;
    Application operator=(const Application &&other) = delete;

  private:
    std::unique_ptr<Window> mWindow;
};

} // namespace engine
