#pragma once

#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace engine
{

#define DEBUGGABLE() virtual void on_debug() override;

class Debuggable;

class Debugger
{
  public:
    static void add_object(Debuggable *o)
    {
        OBJECTS.emplace_back(o);
    }

    static const std::vector<Debuggable *> objects()
    {
        return OBJECTS;
    }

  private:
    Debugger()
    {
    }

    static std::vector<Debuggable *> OBJECTS;
};

class Debuggable
{
  public:
    virtual ~Debuggable()
    {
    }

    virtual void on_debug() = 0;

  protected:
    Debuggable()
    {
        Debugger::add_object(this);
    }
};

} // namespace engine