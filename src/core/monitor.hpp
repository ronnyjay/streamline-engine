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
    operator GLFWmonitor *()
    {
        return mMonitor;
    }

    const char *Title;

    int Width;
    int Height;

    struct
    {
        int MinX;
        int MinY;
        int MaxX;
        int MaxY;
    } WorkArea;

    struct
    {
        float X;
        float Y;
    } ContentScale;

    const std::vector<Resolution> VideoModes;

  private:
    Monitor(GLFWmonitor *monitor);

    GLFWmonitor *mMonitor;

    friend class DisplayMetrics;
};

typedef std::vector<Monitor> MonitorList;

} // namespace engine