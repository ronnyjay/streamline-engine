#pragma once

#include "event.hpp"

class window_close_event : public event
{
  public:
    window_close_event()
    {
        type_ = WindowCloseEvent;
    }
};

class window_resize_event : public event
{
  public:
    window_resize_event(unsigned int width, unsigned int height)
        : width_(width)
        , height_(height)
    {
        type_ = WindowResizeEvent;
    }

    inline unsigned int width() const
    {
        return width_;
    }

    inline unsigned int height() const
    {
        return height_;
    }

  private:
    unsigned int width_, height_;
};
