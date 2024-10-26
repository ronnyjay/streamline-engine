#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "window.hpp"

namespace engine
{

class Application
{
  public:
    Application();

    void     run();

    Window  *GetWindow() const;

    Monitor *GetPrimaryMonitor() const;
    Monitor *GetCurrentMonitor() const;

    ~Application();

    Application(const Application &)             = delete;
    Application(const Application &&)            = delete;

    Application &operator=(const Application &)  = delete;
    Application &operator=(const Application &&) = delete;

  private:
    Window  *mWindow         = nullptr;

    Monitor *mPrimaryMonitor = nullptr;
    Monitor *mCurrentMonitor = nullptr;

  private:
    std::vector<Monitor> mMonitors;
};

} // namespace engine
