#pragma once

#include "monitor.hpp"

namespace engine
{

class DisplayManager
{
  public:
    /**
     * @brief
     *
     */
    DisplayManager()
    {
    }

    /**
     * @brief
     *
     */
    ~DisplayManager()
    {
    }

    /**
     * @brief
     *
     */
    void StartUp()
    {
        int           count;
        GLFWmonitor **monitors = glfwGetMonitors(&count);

        for (int i = 0; i < count; i++)
        {
            mMonitors.emplace_back(Monitor(monitors[i]));
        }
    }

    /**
     * @brief
     *
     */
    void ShutDown()
    {
        mMonitors.clear();
    }

    //

    const MonitorList &MonitorInfo = mMonitors;

    //

    DisplayManager(const DisplayManager &)            = delete;
    DisplayManager(const DisplayManager &&)           = delete;

    DisplayManager operator=(const DisplayManager &)  = delete;
    DisplayManager operator=(const DisplayManager &&) = delete;

  private:
    mutable MonitorList mMonitors;
};

} // namespace engine