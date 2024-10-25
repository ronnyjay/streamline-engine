#pragma once

#include "core/config.hpp"           // IWYU pragma: keep
#include "core/layer.hpp"            // IWYU pragma: keep
#include "core/logger.hpp"           // IWYU pragma: keep
#include "core/resource_manager.hpp" // IWYU pragma: keep
#include "core/window.hpp"           // IWYU pragma: keep
#include "renderer/model.hpp"        // IWYU pragma: keep
#include "renderer/renderer.hpp"     // IWYU pragma: keep
#include "renderer/shader.hpp"       // IWYU pragma: keep
#include "renderer/texture.hpp"      // IWYU pragma: keep
#include "scene/entity.hpp"          // IWYU pragma: keep
#include "scene/scene.hpp"           // IWYU pragma: keep
#include "util/input_manager.hpp"    // IWYU pragma: keep

namespace engine
{

class Application : public Debuggable
{
  public:
    /**
     * @brief Default constructor
     *
     */
    Application();

    /**
     * @brief
     *
     */
    void run();

    /**
     * @brief
     *
     * @return Scene const&
     */
    Scene &scene()
    {
        return m_scene;
    }

    DEBUGGABLE()

    /**
     * @brief Destructor
     *
     */
    ~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    Application(const Application &) = delete;
    Application(const Application &&) = delete;

    Application &operator=(const Application &) = delete;
    Application &operator=(const Application &&) = delete;

  private:
    Config   m_config;
    Window   m_window;
    Scene    m_scene;
    Renderer m_renderer;

    struct
    {
        int vsync = 0;
        int framerate = 0;
    } m_settings;

    struct
    {
        bool first_mouse = true;
        bool show_mouse = true;
        bool capture_mouse = true;
    } m_window_flags;

    struct
    {
        bool show_debug_window = false;
        bool show_debug_metrics = false;
    } m_debug_flags;

    static double      SECONDS_PER_RENDER;
    static double      SECONDS_PER_UPDATE;

    static const char *FRAME_RATE_OPTIONS[];

  private:
    void on_window_resize(FramebufferResizeEvent &);
    void on_key_press(KeyPressEvent &);
    void on_mouse_move(MouseMoveEvent &);
    void on_mouse_scroll(MouseScrollEvent &);
};

} // namespace engine