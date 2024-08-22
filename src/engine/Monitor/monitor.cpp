#include <engine/Logger/Logger.hpp>
#include <engine/Monitor/monitor.hpp>

#include <algorithm>

using namespace engine;

Monitor::Monitor(GLFWmonitor *glfw_monitor)
    : monitor(glfw_monitor)
{
    title = glfwGetMonitorName(monitor);

    glfwGetMonitorWorkarea(glfw_monitor, &position_x, &position_y, &width, &height);
    glfwGetMonitorContentScale(glfw_monitor, &scale_x, &scale_y);

    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(glfw_monitor, &count);

    for (int i = 0; i < count; i++)
    {
        resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
    }

    resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());

    resolution_fullscreen = resolutions.size() - 1;
    resolution_windowed = -1;
    resolution_borderless = resolutions.size() - 1;
}

const bool Monitor::operator==(const Monitor &other) const
{
    return monitor == other.monitor;
}

const bool Monitor::operator!=(const Monitor &other) const
{
    return monitor != other.monitor;
}
