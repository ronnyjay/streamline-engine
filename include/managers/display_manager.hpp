#pragma once

#include "core/display_mode.hpp"
#include "core/monitor.hpp"
#include "core/singleton.hpp"
#include "core/window.hpp"
#include <cassert>

namespace engine
{

class DisplayManager : public Singleton<DisplayManager>
{
  public:
    void Init() override;
    void DeInit() override {};
    void OnEvent(Event &e) override {};

    /**
     * @brief
     *
     * @param window
     */
    void AttachWindow(Window *const window)
    {
        if (window != nullptr)
            mWindow = window;
    }

    /**
     * @brief
     *
     * @param mode
     */
    void SetDisplayMode(WindowMode mode);

    /**
     * @brief
     *
     * @return const MonitorList
     */
    const MonitorList MonitorInfo() const
    {
        return mMonitors;
    }

    /**
     * @brief
     *
     * @return int
     */
    int GetPreferredMonitorIndex() const
    {
        return mPreferredMonitorIndex;
    }

    /**
     * @brief
     *
     * @param index
     */
    void SetPreferredMonitorIndex(int index)
    {
        if (index >= 0 && index < (int)mMonitors.size())
        {
            mPreferredMonitorIndex = index;
        }
    }

  private:
    Window     *mWindow;

    MonitorList mMonitors;

    int         mPreferredMonitorIndex;
};

} // namespace engine