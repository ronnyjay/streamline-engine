#pragma once

#include "event.hpp"

class window_resize_event : public event
{
  public:
    window_resize_event(unsigned int w, unsigned int h)
        : width(w)
        , height(h)
    {
        type_ = WindowResizeEvent;
    }

    unsigned int width;
    unsigned int height;
};
