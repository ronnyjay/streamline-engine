#pragma once

#include "window.hpp"

#include <libstreamline/debug/logger.hpp>

/*
  A wrapper around an opengl/glfw instance
*/
class application
{
  public:
    application()
        : m_log("application")
    {
    }

    void initialize();
    void run();

    ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;

    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

  private:
    window m_window;

    logger m_log;
};
