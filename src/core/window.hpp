#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace engine
{

enum class DisplayMode
{
    Windowed,
    Fullscreen,
    WindowedFullscreen
};

class Window
{
  public:
    Window(int width, int height, const char *title);

  private:
};

}; // namespace engine