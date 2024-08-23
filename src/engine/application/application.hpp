#pragma once

#include "engine/event/event.hpp"
#include "engine/event/window_event.hpp"

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

    void on_event(const event &e);

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
    static application *ref;

    void on_window_close(window_close_event &e);
    void on_window_resize(window_resize_event &e);
};
