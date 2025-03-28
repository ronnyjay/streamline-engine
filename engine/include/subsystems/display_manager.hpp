#pragma once

#include "core/logger.hpp"
#include "core/monitor.hpp"
#include "core/singleton.hpp"

namespace engine
{

struct DisplayManager : public Singleton<DisplayManager>
{
    DisplayManager()
    {
        Logger::info("Detecting displays");

        int           count;
        GLFWmonitor **monitors = glfwGetMonitors(&count);

        for (int i = 0; i < count; i++)
        {
            std::unique_ptr<Monitor> monitor = std::make_unique<Monitor>(monitors[i]);
            Logger::info("Found display: %s", monitor.get()->title);
            m_monitors.emplace_back(std::move(monitor));
        }
    }

    Monitor *primaryMonitor;
    Monitor *currentMonitor;

    void     detectCurrentDisplay()
    {
    }

  private:
    std::vector<std::unique_ptr<Monitor>> m_monitors;
};

} // namespace engine