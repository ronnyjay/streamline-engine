#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "assert.hpp"    // IWYU pragma: keep
#include "event.hpp"     // IWYU pragma: keep
#include "setup.hpp"     // IWYU pragma: keep
#include "singleton.hpp" // IWYU pragma: keep

#include "math/vec2.hpp" // IWYU pragma: keep

namespace engine
{

enum class window_mode
{
    windowed,
    fullscreen,
    windowed_fullscreen
};

class window
{
    GLFWwindow *m_glfwWindow;

    ivec2 m_lastSize;
    ivec2 m_lastPos;

    struct cursor_flags
    {
        bool entered;
        bool visible;
    } m_cursorFlags;

    window_mode m_windowMode;

    event_callback m_eventCallback;

  public:
    /**
     * @brief
     *
     * @param width
     * @param height
     * @param title
     */
    window(int width, int height, const char *title);

    /**
     * @brief
     *
     */
    ~window()
    {
        if (m_glfwWindow)
            glfwDestroyWindow(m_glfwWindow);

        glfwTerminate();
    }

    window(window const &)  = delete;
    window(window const &&) = delete;

    window operator=(window const &)  = delete;
    window operator=(window const &&) = delete;

    /**
     * @brief
     *
     * @return GLFWwindow *
     */
    operator GLFWwindow *()
    {
        return m_glfwWindow;
    }

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool isOpen() const;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool isVisible() const;

    /**
     * @brief
     *
     */
    void show();

    /**
     * @brief
     *
     */
    void hide();

    /**
     * @brief
     *
     */
    void swapBuffers();

    /**
     * @brief
     *
     */
    void pollEvents();

    /**
     * @brief
     *
     */
    void toggleCursor();

    /**
     * @brief
     *
     * @return ivec2
     */
    const ivec2 &getPositionInScreen() const;

    /**
     * @brief
     *
     * @return ivec2
     */
    const ivec2 &getSizeInScreen() const;

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void moveTo(int x, int y);

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void resize(int x, int y);

    /**
     * @brief
     *
     * @param mode
     */
    void setWindowMode(window_mode mode);

    /**
     * @brief
     *
     * @tparam T
     * @param instance
     * @param fn
     */
    template <typename T>
    void setEventCallback(T *instance, void (T::*fn)(event &&e))
    {
        m_eventCallback = [instance, fn](event &&event) { (instance->*fn)(std::move(event)); };
    }

  private:
    static void framebuffer_callback(GLFWwindow *window, int width, int height);

    static void maximize_callback(GLFWwindow *window, int maximize);
    static void minimize_callback(GLFWwindow *window, int minimize);

    static void cursor_callback(GLFWwindow *window, double x, double y);
    static void scroll_callback(GLFWwindow *window, double x, double y);

    static void mouse_callback(GLFWwindow *window, int button, int action, int mods);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

} // namespace engine
