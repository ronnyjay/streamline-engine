#pragma once

#include "singleton.hpp"

namespace engine
{

struct DebugWindow : public Singleton<DebugWindow>
{
    bool b_showWindow  = false;
    bool b_showMetrics = false;

    DebugWindow();

    void draw();

    ~DebugWindow();

  private:
    void drawVideoSettings();
    void drawSceneSettings();
};

} // namespace engine
