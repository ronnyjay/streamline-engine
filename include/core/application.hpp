#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "specification.hpp"
#include "window.hpp"

namespace engine
{

class Specification;

class Application
{
  public:
    Application(Specification &&);

    void          Run();

    Window *const GetWindow() const
    {
        return mWindow;
    }

    Monitor *const GetPrimaryMonitor() const
    {
        return mPrimaryMonitor;
    }

    Monitor *const GetCurrentMonitor() const
    {
        return mCurrentMonitor;
    }

    ~Application();

    Application(const Application &)             = delete;
    Application(const Application &&)            = delete;

    Application &operator=(const Application &)  = delete;
    Application &operator=(const Application &&) = delete;

  private:
    Specification &mSpecification;

    Window        *mWindow         = nullptr;

    Monitor       *mPrimaryMonitor = nullptr;
    Monitor       *mCurrentMonitor = nullptr;

  private:
    std::vector<Monitor> mMonitors;
};

} // namespace engine
