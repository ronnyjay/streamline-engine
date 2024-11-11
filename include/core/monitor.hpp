#pragma once

#include "video.hpp"

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
        return mMonitor;
    }

    const char *Title;

    int         Width;
    int         Height;

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

    std::vector<Resolution>  Resolutions;
    std::vector<RefreshRate> RefreshRates;

  private:
    GLFWmonitor *mMonitor;
};

typedef std::vector<Monitor> MonitorList;

} // namespace engine