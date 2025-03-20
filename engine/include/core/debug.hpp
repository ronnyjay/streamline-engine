#pragma once

#include "singleton.hpp"
#include "window.hpp"

namespace engine
{

struct DebugWindow : public Singleton<DebugWindow>
{
    bool b_showWindow  = false;
    bool b_showMetrics = false;

    DebugWindow();

    void draw();

    ~DebugWindow();
};

} // namespace engine
