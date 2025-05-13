#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <algorithm>
#include <vector>

#include "resolution.hpp"

namespace engine
{

struct Monitor
{
    Monitor(GLFWmonitor *monitor)
        : monitor(monitor)
    {
        title = glfwGetMonitorName(monitor);

        glfwGetMonitorPos(monitor, &positionX, &positionY);
        glfwGetMonitorContentScale(monitor, &scaleX, &scaleY);

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        width                   = mode->width;
        height                  = mode->height;

        int                count;
        const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

        for (int i = 0; i < count; i++)
        {
            resolutions.emplace_back(Resolution(modes[i].width, modes[i].height));
        }

        resolutions.erase(std::unique(resolutions.begin(), resolutions.end()), resolutions.end());
    }

    bool operator==(const Monitor &other) const
    {
        return monitor == other.monitor;
    }

    bool operator!=(const Monitor &other) const
    {
        return monitor != other.monitor;
    }

    GLFWmonitor            *monitor;

    int                     width;
    int                     height;

    int                     positionX;
    int                     positionY;

    float                   scaleX;
    float                   scaleY;

    const char             *title;

    std::vector<Resolution> resolutions;
};

} // namespace engine
