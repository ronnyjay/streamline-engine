#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "resolution.hpp"

#include <vector>

struct monitor
{
    monitor(GLFWmonitor *const);
    monitor(const monitor &) = default;

    const bool operator==(const monitor &) const;
    const bool operator!=(const monitor &) const;

    int width;
    int height;

    int position_x;
    int position_y;

    float scale_x;
    float scale_y;

    const char *title;

    GLFWmonitor *gl_monitor;

    // index of the fullscreen resoltuion
    int resolution_fullscreen;

    // index of the windowed resolution
    int resolution_windowed;

    // index of the borderless resolution
    int resolution_borderless;

    std::vector<resolution> resolutions;
};
