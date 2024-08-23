#pragma once

#include "event.hpp"

class mouse_event : public event
{
  public:
    mouse_event(double xpos_in, double ypos_in)
    {
    }

  private:
    double xpos_in_, ypos_in_;
};