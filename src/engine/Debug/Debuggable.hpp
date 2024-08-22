#pragma once

#include <imgui.h>

namespace engine
{

class Debuggable
{
  public:
    Debuggable()
    {
    }

    virtual void draw_debug_info(){};

    virtual ~Debuggable()
    {
    }
};

} // namespace engine