#include "core/settings.hpp"

#include "core/renderer.hpp"
#include "core/window.hpp"
#include "subsystems/display_manager.hpp"

using namespace engine;

void UserSettings::apply()
{
    Monitor *currentMonitor = DisplayManager::getInstance().getCurrentMonitor();

    m_currMonitorIndex      = m_nextMonitorIndex;
    m_currWindowMode        = m_nextWindowMode;
    m_currResolution        = m_nextResolution;
    m_currVerticalSync      = m_nextVerticalSync;

    Window::getInstance().setWindowMode(m_currWindowMode);

    if (m_nextWindowMode == WindowMode::Windowed || m_nextWindowMode == WindowMode::WindowedFullscreen)
    {
        float sizeX     = m_nextResolution.width / currentMonitor->scaleX;
        float sizeY     = m_nextResolution.height / currentMonitor->scaleY;

        float positionX = (currentMonitor->width - sizeX) / 2.0f;
        float positionY = (currentMonitor->height - sizeY) / 2.0f;

        Window::getInstance().resize(sizeX, sizeY);
        Window::getInstance().moveTo(positionX, positionY);
    }

    Renderer::getInstance().setResolution(m_currResolution);

    Renderer::getInstance().setVerticalSync(m_currVerticalSync);
}

bool UserSettings::hasUnsavedChanges() const
{
    return ((m_currMonitorIndex != m_nextMonitorIndex) || (m_currWindowMode != m_nextWindowMode) ||
            (m_currResolution != m_nextResolution) || (m_currVerticalSync != m_nextVerticalSync));
}