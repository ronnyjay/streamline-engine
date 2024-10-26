#pragma once

#include "resolution.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <vector>

namespace engine
{

struct Monitor
{
    Monitor(GLFWmonitor *monitor);

    operator GLFWmonitor *()
    {
        return mMonitor;
    }

    bool operator==(const Monitor &other)
    {
        return mMonitor == other.mMonitor;
    }

    bool operator!=(const Monitor &other)
    {
        return mMonitor != other.mMonitor;
    }

    int                     StartX;
    int                     StartY;

    int                     Width;
    int                     Height;

    float                   ScaleX;
    float                   ScaleY;

    const char             *Title;

    std::vector<Resolution> Resolutions;

  private:
    GLFWmonitor *mMonitor;
};

} // namespace engine