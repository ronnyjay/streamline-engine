#pragma once

#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace engine
{

class Debuggable
{
  public:
    Debuggable(const std::string &identifier) : m_identifier(identifier)
    {
    }

    virtual void draw_debug_info() = 0;

    const std::string &identifier()
    {
        return m_identifier;
    }

  private:
    std::string m_identifier;
};

}; // namespace engine