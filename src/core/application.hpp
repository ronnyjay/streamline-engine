#pragma once

#include "window.hpp"

namespace engine
{

enum class Level
{
    Info,
    Warn,
    Error
};

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

    void AddDebugMessage(Level, const std::string &);

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
