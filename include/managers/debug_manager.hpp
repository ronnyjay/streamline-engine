#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "core/singleton.hpp"

namespace engine
{

class DebugManager : public Singleton<DebugManager>
{
  public:
    /** @brief Default constructor  */
    DebugManager()
        : mShowDebugWindow(true)
        , mShowDebugMetrics(false)
    {
    }

    void Draw();

    void Init() override;
    void DeInit() override;

    void OnEvent(Event &e) override;

  private:
    bool mShowDebugWindow;
    bool mShowDebugMetrics;

    bool OnKeyPress(KeyPressEvent &e);
};

} // namespace engine