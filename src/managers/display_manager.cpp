#include "managers/display_manager.hpp"

using namespace engine;

void DisplayManager::Init()
{
    // Load monitors
    // Eventually do this with PAL
    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        mMonitors.emplace_back(Monitor(monitors[i]));
    }

    mPreferredMonitorIndex = 0; // Always guaranteed to be the OS's primary monitor
}

void DisplayManager::SetDisplayMode(WindowMode mode)
{
    assert(mWindow != nullptr && "No window attached!");

    const Monitor &monitor = mMonitors[mPreferredMonitorIndex];

    switch (mode)
    {
    // Window will fullscreen to the nearest monitor.
    // So, move the window to the preferred monitor.
    case WindowMode::Fullscreen:
    case WindowMode::FullscreenBorderless:
        mWindow->MoveTo(monitor.WorkArea.MinX, monitor.WorkArea.MinY);
        break;
    // Do nothing for windowed mode.
    // Window will handle pos, size.
    default:
        break;
    }

    mWindow->SetWindowMode(mode);
}