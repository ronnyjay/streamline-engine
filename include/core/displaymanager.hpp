#pragma once

#include "monitor.hpp"
#include "window.hpp"

namespace engine
{

enum class DisplayMode
{
    Windowed,
    ExclusiveFullscreen,
    BorderlessFullscreen,
};

class DisplayManager
{
  public:
    /**
     * @brief
     *
     */
    DisplayManager(Window *window)
        : m_preferred_monitor_index(0)
    {
        int           count;
        GLFWmonitor **monitors = glfwGetMonitors(&count);

        for (int i = 0; i < count; i++)
        {
            m_monitors.emplace_back(Monitor(monitors[i]));
        }
    } // namespace engine

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
     * @return const MonitorList&
     */
    const MonitorList &monitors() const
    {
        return m_monitors;
    }

    /**
     * @brief
     *
     * @param index
     */
    bool set_preferred_monitor_index(int index)
    {
        if (index >= 0 && index < static_cast<int>(m_monitors.size()))
        {
            m_preferred_monitor_index = index;

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
    int get_preferred_monitor_index() const
    {
        return m_preferred_monitor_index;
    }

    DisplayManager(const DisplayManager &) = delete;
    DisplayManager(const DisplayManager &&) = delete;

    DisplayManager operator=(const DisplayManager &) = delete;
    DisplayManager operator=(const DisplayManager &&) = delete;

  private:
    Window     *m_window_handle;

    MonitorList m_monitors;

    // refresh rates
    // resolutions per display

    // display mode

    int m_preferred_monitor_index;
};

} // namespace engine