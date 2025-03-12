#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

struct monitor
{
    GLFWmonitor *m_glfwMonitor;
};

} // namespace engine
