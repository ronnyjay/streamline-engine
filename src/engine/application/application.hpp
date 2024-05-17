#pragma once

#include <engine/camera/camera.hpp>
#include <engine/window/window.hpp>
#include <engine/world/world.hpp>

#include <map>

namespace engine
{

typedef std::map<int, Camera *> CameraMap;
typedef std::map<int, World *> WorldMap;
typedef std::unordered_map<int, CameraDirection> KeybindMap;

struct ApplicationFlags
{
    bool has_mouse = false;
    bool capture_mouse = false;
    bool show_wireframes = false;
    bool show_collisions = false;
    bool show_metrics = false;
    bool show_debug_window = false;
};

class Application
{
  public:
    Application();

    Window *const window() const;
    void set_window(Window *const);

    Camera *const camera() const;
    void add_camera(int, Camera *const);
    void set_camera(int);

    World *const world() const;
    void add_world(int, World *const);
    void set_world(int);

    ApplicationFlags const &flags() const;

    void bind_movement_key(int, const CameraDirection);
    void run();

    ~Application();

  private:
    Window *m_window;

    Camera *m_camera;
    CameraMap m_cameras;

    World *m_world;
    WorldMap m_worlds;

    KeybindMap m_keybinds;
    ApplicationFlags m_flags;

    float m_cursor_x;
    float m_cursor_y;

    void process_input();

    void toggle_wireframes();

    void set_camera_next();
    void set_camera_previous();

    void set_world_next();
    void set_world_previous();

    static void framebuffer_size_callback(GLFWwindow *, int, int);
    static void minimize_callback(GLFWwindow *, int);
    static void maximize_callback(GLFWwindow *, int);
    static void key_callback(GLFWwindow *, int, int, int, int);
    static void cursor_callback(GLFWwindow *, double, double);
    static void scroll_callback(GLFWwindow *, double, double);
};

}; // namespace engine
