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

    int y;
    int x;

    int width;
    int height;

    struct
    {
        float x;
        float y;
    } scale;

    const char *title;

    GLFWmonitor *glfw_monitor;

    struct
    {
        int fullscreen;
        int windowed;
        int borderless;
    } active_resolutions;

    std::vector<resolution> resolutions;
};
