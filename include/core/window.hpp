#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "event.hpp"      // IWYU pragma: keep
#include "events.hpp"     // IWYU pragma: keep
#include "monitor.hpp"    // IWYU pragma: keep
#include "resolution.hpp" // IWYU pragma: keep

namespace engine
{

class Window : public EventDispatcher
{
  public:
    /**
     * @brief Default constructor
     *
     */
    Window();

    /**
     * @brief
     *
     * @return GLFWwindow *
     */
    operator GLFWwindow *()
    {
        return m_window;
    }

    /**
     * @brief
     *
     * @param width
     * @param height
     * @param title
     */
    void create(int width, int height, const char *title);

    /**
     * @brief Default destructor
     *
     */
    ~Window() {};

    Window(const Window &) = delete;
    Window(const Window &&) = delete;

    Window operator=(const Window &) = delete;
    Window operator=(const Window &&) = delete;

  private:
    GLFWwindow *m_window;
};

} // namespace engine