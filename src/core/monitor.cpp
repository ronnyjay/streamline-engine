#include "core/monitor.hpp"

using namespace engine;

Monitor::Monitor(GLFWmonitor *monitor)
    : mMonitor(monitor)
{
    Title = glfwGetMonitorName(monitor);

    glfwGetMonitorWorkarea(monitor, &StartX, &StartY, &Width, &Height);
    glfwGetMonitorContentScale(monitor, &ScaleX, &ScaleY);

    int                count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    for (int i = 0; i < count; i++)
    {
        Resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    Resolutions.erase(std::unique(Resolutions.begin(), Resolutions.end()), Resolutions.end());
}