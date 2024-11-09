#pragma once

#include "resolution.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <vector>

namespace engine
{

struct Monitor
{
    Monitor(GLFWmonitor *monitor);

    operator GLFWmonitor *()
    {
        return monitor;
    }

    const char *title;

    int         width;
    int         height;

    struct
    {
        int min_x;
        int min_y;
        int max_x;
        int max_y;
    } work_area;

    struct
    {
        float x;
        float y;
    } content_scale;

    const std::vector<Resolution> video_modes;

  private:
    GLFWmonitor *monitor;
};

typedef std::vector<Monitor> MonitorList;

} // namespace engine