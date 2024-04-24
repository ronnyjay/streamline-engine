#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

// #include <engine/camera/camera.hpp>
#include <engine/config/config.hpp>
#include <engine/debugger/debugger.hpp>
#include <engine/stb/stb_image.hpp>

#include <irrklang/ik_ISoundEngine.h>
#include <irrklang/irrKlang.h>

#include <unordered_map>

namespace engine
{

namespace camera
{
class camera_t;
};

class window
{
  public:
    window();
    window(int, int, const char *);

    void configure(config);
    void initialize();

    void add_camera(int, camera::camera_t *);
    void set_camera(int);
    void toggle_camera();

    void process_input();

    GLFWwindow *const as_glfw_window() const
    {
        return m_window;
    }

    debugger &debug_window()
    {
        return m_debugger;
    }

    int width()
    {
        return m_window_width;
    }

    int height()
    {
        return m_window_height;
    }

    camera::camera_t *const camera() const
    {
        return m_camera;
    }

    irrklang::ISoundEngine *const sound_engine() const
    {
        return m_sound_engine;
    }

    bool running()
    {
        return !glfwWindowShouldClose(m_window);
    }

  private:
    static void resize_callback(GLFWwindow *, int, int);
    static void minimized_callback(GLFWwindow *, int);
    static void maximized_callback(GLFWwindow *, int);
    static void key_callback(GLFWwindow *, int, int, int, int);
    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);

  private:
    GLFWwindow *m_window;
    debugger m_debugger;

    int m_window_width;
    int m_window_height;
    const char *m_window_title;

    float m_cursor_x;
    float m_cursor_y;
    bool m_capture_mouse;

    camera::camera_t *m_camera;
    std::string m_camera_title;

    irrklang::ISoundEngine *m_sound_engine;
    std::unordered_map<int, camera::camera_t *> m_cameras;
};

}; // namespace engine