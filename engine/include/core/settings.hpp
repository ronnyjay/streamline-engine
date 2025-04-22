#pragma once

#include "core/resolution.hpp"
#include "core/window.hpp"
#include "singleton.hpp"

namespace engine
{

struct UserSettings : public Singleton<UserSettings>
{
    explicit UserSettings()
        : m_currWindowMode(WindowMode::Windowed)
        , m_nextWindowMode(WindowMode::Windowed)
        , m_currResolution(800, 600)
        , m_nextResolution(800, 600)
    {
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

    void discard()
    {
        m_nextWindowMode = m_currWindowMode;
        m_nextResolution = m_currResolution;
    }

    void apply();

    bool hasUnsavedChanges() const
    {
        return (m_currWindowMode != m_nextWindowMode) || (m_currResolution != m_nextResolution);
    }

  private:
    WindowMode m_currWindowMode;
    WindowMode m_nextWindowMode;
    Resolution m_currResolution;
    Resolution m_nextResolution;
};

} // namespace engine