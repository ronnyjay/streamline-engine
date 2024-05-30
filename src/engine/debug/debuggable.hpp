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

    virtual void DrawDebugInfo() {};

    virtual ~Debuggable()
    {
    }
};

}; // namespace engine