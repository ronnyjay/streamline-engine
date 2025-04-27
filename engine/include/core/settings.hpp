#pragma once

#include "core/resolution.hpp"
#include "core/singleton.hpp"
#include "core/window.hpp"

namespace engine
{

struct UserSettings : public Singleton<UserSettings>
{

    explicit UserSettings()
        : m_currMonitorIndex(0)
        , m_nextMonitorIndex(0)
        , m_currWindowMode(WindowMode::Windowed)
        , m_nextWindowMode(WindowMode::Windowed)
        , m_currResolution(800, 600)
        , m_nextResolution(800, 600)
        , m_currVerticalSync(1)
        , m_nextVerticalSync(1)
    {
    }

    void setPrimaryMonitor(int monitor)
    {
        m_nextMonitorIndex = monitor;
    }

    int getPrimaryMonitor() const
    {
        return m_nextMonitorIndex;
    }

    void setWindowMode(WindowMode mode)
    {
        m_nextWindowMode = mode;
    }

    WindowMode getWindowMode() const
    {
        return m_nextWindowMode;
    }

    void setResolution(Resolution res)
    {
        m_nextResolution = res;
    }

    Resolution getResolution() const
    {
        return m_nextResolution;
    }

    void setVerticalSync(bool vsync)
    {
        m_nextVerticalSync = vsync;
    }

    bool getVerticalSync() const
    {
        return m_nextVerticalSync;
    }

    void discard()
    {
        m_nextWindowMode = m_currWindowMode;
        m_nextResolution = m_currResolution;
    }

    void apply();

    bool hasUnsavedChanges() const;

  private:
    int        m_currMonitorIndex;
    int        m_nextMonitorIndex;
    WindowMode m_currWindowMode;
    WindowMode m_nextWindowMode;
    Resolution m_currResolution;
    Resolution m_nextResolution;
    bool       m_currVerticalSync;
    bool       m_nextVerticalSync;

    // Utility functions

    bool hasMonitorChanged() const
    {
        return m_currMonitorIndex != m_nextMonitorIndex;
    }

    bool hasWindowModeChanged() const
    {
        return m_currWindowMode != m_nextWindowMode;
    }

    bool hasResolutionChanged() const
    {
        return m_currResolution != m_nextResolution;
    }

    bool hasVerticalSyncChanged() const
    {
        return m_currVerticalSync != m_nextVerticalSync;
    }
};

} // namespace engine