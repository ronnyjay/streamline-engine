#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <engine/Resolution/resolution.hpp>

#include <vector>

namespace engine
{

struct Monitor
{
    Monitor(GLFWmonitor *);
    Monitor(const Monitor &) = default;

    const bool operator==(const Monitor &) const;
    const bool operator!=(const Monitor &) const;

    int width;
    int height;

    int position_x;
    int position_y;

    float scale_x;
    float scale_y;

    const char *title;

    GLFWmonitor *monitor;

    // index of the fullscreen resoltuion
    int resolution_fullscreen;

    // index of the windowed resolution
    int resolution_windowed;

    // index of the borderless resolution
    int resolution_borderless;

    std::vector<Resolution> resolutions;
};

} // namespace engine