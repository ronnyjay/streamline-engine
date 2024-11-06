#pragma once

#include "window.hpp"

namespace engine
{

class Application
{
  public:
    static Application &Get()
    {
        if (!kInstance)
        {
            kInstance = std::unique_ptr<Application>(new Application);
        }

        return *kInstance;
    }

    void Run();

    Window *const GetTopLevelWindow()
    {
        return mWindow.get();
    }

    ~Application();

    Application(const Application &other) = delete;
    Application(const Application &&other) = delete;

    Application operator=(const Application &other) = delete;
    Application operator=(const Application &&other) = delete;

  private:
    Application();

    std::unique_ptr<Window> mWindow;

    static std::unique_ptr<Application> kInstance;
};

} // namespace engine
