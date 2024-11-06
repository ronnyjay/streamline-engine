#include "monitor.hpp"
#include <algorithm>

using namespace engine;

Monitor::Monitor(GLFWmonitor *monitor) : mMonitor(monitor)
{
    Title = glfwGetMonitorName(monitor);

    glfwGetMonitorContentScale(monitor, &ContentScale.X, &ContentScale.Y);
    glfwGetMonitorWorkarea(monitor, &WorkArea.MinX, &WorkArea.MinY, &Width, &Height);

    WorkArea.MaxX = WorkArea.MinX + Width;
    WorkArea.MaxY = WorkArea.MinY + Height;

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    for (int i = 0; i < count; i++)
    {
        const_cast<std::vector<Resolution> &>(VideoModes).emplace_back(Resolution{modes[i].width, modes[i].height});
    }

    // GLFWvidmode contains duplicate dimensions per refresh rates.
    // This could be something configured by the developer,
    // but discard for now.
    const_cast<std::vector<Resolution> &>(VideoModes)
        .erase(std::unique(const_cast<std::vector<Resolution> &>(VideoModes).begin(),
                           const_cast<std::vector<Resolution> &>(VideoModes).end()),
               const_cast<std::vector<Resolution> &>(VideoModes).end());
}