#include <core/monitor.hpp>
#include <algorithm>

using namespace engine;

Monitor::Monitor(GLFWmonitor *monitor)
    : monitor(monitor)
{
    title = glfwGetMonitorName(monitor);

    glfwGetMonitorContentScale(monitor, &content_scale.x, &content_scale.y);
    glfwGetMonitorWorkarea(monitor, &work_area.min_x, &work_area.min_y, &width, &height);

    work_area.max_x = work_area.min_x + width;
    work_area.max_y = work_area.min_y + height;

    int                count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    for (int i = 0; i < count; i++)
    {
        const_cast<std::vector<Resolution> &>(video_modes).emplace_back(Resolution{modes[i].width, modes[i].height});
    }

    // GLFWvidmode contains duplicate dimensions per refresh rates.
    // This could be something configured by the developer,
    // but discard for now.
    const_cast<std::vector<Resolution> &>(video_modes)
        .erase(
            std::unique(
                const_cast<std::vector<Resolution> &>(video_modes).begin(),
                const_cast<std::vector<Resolution> &>(video_modes).end()),
            const_cast<std::vector<Resolution> &>(video_modes).end());
}