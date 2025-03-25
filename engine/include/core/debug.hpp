#pragma once

#include "singleton.hpp"

#include <memory>
#include <vector>

namespace engine
{

struct DebugPanel
{
    virtual ~DebugPanel() = default;

    virtual void draw() = 0;
};

struct DebugWindow : public Singleton<DebugWindow>
{
    bool b_showWindow  = false;
    bool b_showMetrics = false;

    DebugWindow();

    void draw();

    ~DebugWindow();

  private:
    std::vector<std::unique_ptr<DebugPanel>> m_debugPanels;
};

} // namespace engine
