#include "monitor.hpp"

#include <algorithm>

monitor::monitor(GLFWmonitor *const m)
    : gl_monitor(m)
{
    title = glfwGetMonitorName(gl_monitor);

    glfwGetMonitorWorkarea(gl_monitor, &position_x, &position_y, &width, &height);
    glfwGetMonitorContentScale(gl_monitor, &scale_x, &scale_y);

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(gl_monitor, &count);

    for (int i = 0; i < count; i++)
    {
        resolutions.emplace_back(resolution(modes[i].width, modes[i].height));
    }

    resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());

    resolution_fullscreen = resolutions.size() - 1;
    resolution_windowed = -1;
    resolution_borderless = resolutions.size() - 1;
}

const bool monitor::operator==(const monitor &other) const
{
    return gl_monitor == other.gl_monitor;
}

const bool monitor::operator!=(const monitor &other) const
{
    return gl_monitor != other.gl_monitor;
}
