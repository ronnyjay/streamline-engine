#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <memory>

namespace engine
{

class Window
{
  public:
    static std::unique_ptr<Window> Create(int width, int height, const char *title)
    {
        return std::unique_ptr<Window>(new Window(width, height, title));
    }

    void SetWindowPosition(int, int);
    void SetWindowSize(int, int);

    void SetFullscreen();
    void SetWindowed();
    void SetBorderless();

    int GetX() const
    {
        return mX;
    }

    int GetY() const
    {
        return mY;
    }

    int GetWidth() const
    {
        return mWidth;
    }

    int GetHeight() const
    {
        return mHeight;
    }

    ~Window();

    Window(const Window &other) = delete;
    Window(const Window &&other) = delete;

    Window operator=(const Window &other) = delete;
    Window operator=(const Window &&other) = delete;

  private:
    GLFWwindow *mWindow;

    int mX;
    int mY;

    int mWidth;
    int mHeight;

    Window(int width, int height, const char *title);
};

}; // namespace engine