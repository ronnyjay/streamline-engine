#pragma once

#include "window.hpp"

namespace engine
{

class Application
{
  public:
    Application()
    {
    }

    ~Application() = default;

    Application(const Application &) = delete;
    Application(const Application &&) = delete;

    Application &operator=(const Application &) = delete;
    Application &operator=(const Application &&) = delete;

  private:
    Window m_window;
};

} // namespace engine
