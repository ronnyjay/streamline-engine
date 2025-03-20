#pragma once

#include "singleton.hpp"
#include "window.hpp"

namespace engine
{

struct DebugWindow : public Singleton<DebugWindow>
{
    bool showDebugWindow  = false;
    bool showDebugMetrics = false;

    DebugWindow();

    void draw();

    ~DebugWindow();
};

} // namespace engine
