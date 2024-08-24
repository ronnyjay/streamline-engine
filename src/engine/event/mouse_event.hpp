#pragma once

#include "event.hpp"

class mouse_event : public event
{
  public:
    mouse_event(double xpos_in, double ypos_in)
    {
    }

    double x_offset;
    double y_offset;
};