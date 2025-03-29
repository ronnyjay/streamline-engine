#pragma once

#include "core/monitor.hpp"
#include "core/singleton.hpp"

#include <memory>

namespace engine
{

struct DisplayManager : public Singleton<DisplayManager>
{
    DisplayManager();

    // clang-format off
    Monitor *const getPrimaryMonitor() const;
    Monitor *const getCurrentMonitor() const;
    // clang-format on

    std::vector<std::unique_ptr<Monitor>> const &getMonitors() const
    {
        return m_monitors;
    }

  private:
    std::vector<std::unique_ptr<Monitor>> m_monitors;
};

} // namespace engine