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
        : mPreferredMonitorIndex(0)
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

    /**
     * @brief
     *
     * @param index
     */
    bool SetPreferredMonitorIndex(int index)
    {
        if (index >= 0 && index < static_cast<int>(mMonitors.size()))
        {
            mPreferredMonitorIndex = index;

            return true;
        }

        return false;
    }

    /**
     * @brief
     *
     * @param index
     * @return int
     */
    int GetPreferredMonitorIndex() const
    {
        return mPreferredMonitorIndex;
    }

    //

    const MonitorList &MonitorInfo = mMonitors;

    //

    DisplayManager(const DisplayManager &) = delete;
    DisplayManager(const DisplayManager &&) = delete;

    DisplayManager operator=(const DisplayManager &) = delete;
    DisplayManager operator=(const DisplayManager &&) = delete;

  private:
    MonitorList mMonitors;

    int         mPreferredMonitorIndex;
};

} // namespace engine