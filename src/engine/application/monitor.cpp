#include "monitor.hpp"

#include <algorithm>

monitor::monitor(GLFWmonitor *const m)
    : glfw_monitor(m)
{
    title = glfwGetMonitorName(glfw_monitor);

    glfwGetMonitorWorkarea(glfw_monitor, &position_x, &position_y, &width, &height);
    glfwGetMonitorContentScale(glfw_monitor, &scale_x, &scale_y);

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(glfw_monitor, &count);

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
    return glfw_monitor == other.glfw_monitor;
}

const bool monitor::operator!=(const monitor &other) const
{
    return glfw_monitor != other.glfw_monitor;
}
