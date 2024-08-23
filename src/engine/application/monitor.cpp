#include "monitor.hpp"

#include <algorithm>

monitor::monitor(GLFWmonitor *const m)
    : glfw_monitor(m)
{
    title = glfwGetMonitorName(glfw_monitor);

    glfwGetMonitorWorkarea(glfw_monitor, &x, &y, &width, &height);
    glfwGetMonitorContentScale(glfw_monitor, &scale_x, &scale_y);

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(glfw_monitor, &count);

    for (int i = 0; i < count; i++)
    {
        resolutions.emplace_back(resolution(modes[i].width, modes[i].height));
    }

    resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());

    active_resolutions.fullscreen = resolutions.size() - 1;
    active_resolutions.windowed = -1;
    active_resolutions.borderless = resolutions.size() - 1;
}

const bool monitor::operator==(const monitor &other) const
{
    return glfw_monitor == other.glfw_monitor;
}

const bool monitor::operator!=(const monitor &other) const
{
    return glfw_monitor != other.glfw_monitor;
}
