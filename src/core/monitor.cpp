#include <algorithm>
#include <core/monitor.hpp>

using namespace engine;

Monitor::Monitor(GLFWmonitor *monitor)
    : mMonitor(monitor)
{
    Title = glfwGetMonitorName(monitor);

    glfwGetMonitorContentScale(monitor, &ContentScale.X, &ContentScale.Y);
    glfwGetMonitorWorkarea(monitor, &WorkArea.MinX, &WorkArea.MinY, &Width, &Height);

    WorkArea.MaxX = WorkArea.MaxY + Width;
    WorkArea.MaxY = WorkArea.MinY + Height;

    int                count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    for (int i = 0; i < count; i++)
    {
        Resolutions.emplace_back(Resolution{modes[i].width, modes[i].height});
        RefreshRates.emplace_back(RefreshRate{modes[i].refreshRate});
    }

    // GLFWvidmode contains duplicate dimensions per refresh rates.
    // Store both seperately and erase duplicates in each respective container
    Resolutions.erase(std::unique(Resolutions.begin(), Resolutions.end()), Resolutions.end());
    RefreshRates.erase(std::unique(RefreshRates.begin(), RefreshRates.end()), RefreshRates.end());
}