#include "core/settings.hpp"

#include "core/renderer.hpp"
#include "core/window.hpp"

#include "subsystems/display_manager.hpp"

using namespace engine;

void UserSettings::apply()
{
    if (!hasUnsavedChanges())
    {
        return;
    }

    Monitor *currentMonitor = DisplayManager::getInstance().getCurrentMonitor();

    if (hasWindowModeChanged())
    {
        Window::getInstance().setWindowMode(m_nextWindowMode);
    }

    float sizeX     = m_nextResolution.width / currentMonitor->scaleX;
    float sizeY     = m_nextResolution.height / currentMonitor->scaleY;

    float spaceX    = (currentMonitor->width - sizeX);
    float spaceY    = (currentMonitor->height - sizeY);

    float positionX = 0;
    float positionY = 0;

    if (spaceX > 0 && spaceY > 0)
    {
        positionX = spaceX / 2.0f;
        positionY = spaceY / 2.0f;
    }

    Window::getInstance().resize(sizeX, sizeY);
    Window::getInstance().moveTo(positionX, positionY);

    Renderer::getInstance().setResolution(m_nextResolution);

    if (hasVerticalSyncChanged())
    {
        Renderer::getInstance().setVerticalSync(m_nextVerticalSync);
    }

    m_currMonitorIndex = m_nextMonitorIndex;
    m_currWindowMode   = m_nextWindowMode;
    m_currResolution   = m_nextResolution;
    m_currVerticalSync = m_nextVerticalSync;
}

bool UserSettings::hasUnsavedChanges() const
{
    return hasMonitorChanged() || hasWindowModeChanged() || hasResolutionChanged() || hasVerticalSyncChanged();
}