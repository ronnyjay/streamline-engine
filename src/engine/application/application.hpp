#pragma once

#include "window.hpp"

#include <libstreamline/config/config.hpp>

class application
{
  public:
    application();

    static application &get()
    {
        if (!ref)
            ref = new application;

        return *ref;
    }

    void run();

    static void reset()
    {
        delete ref;
        ref = nullptr;
    }

    ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;

    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

  private:
    config m_config;
    window m_window;

    static application *ref;
};
