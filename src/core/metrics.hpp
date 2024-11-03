#pragma once

#include "monitor.hpp"

namespace engine
{

class DisplayMetrics
{
  public:
    DisplayMetrics()
    {
    }

    const MonitorList MonitorInfo;

    static void GetDisplayMetrics(DisplayMetrics &metrics)
    {
        LoadMonitors(metrics);
    }

  private:
    static void LoadMonitors(DisplayMetrics &metrics)
    {
        int count;
        GLFWmonitor **monitors = glfwGetMonitors(&count);

        for (int i = 0; i < count; i++)
        {
            const_cast<MonitorList &>(metrics.MonitorInfo).emplace_back(Monitor(monitors[i]));
        }
    }
};

} // namespace engine