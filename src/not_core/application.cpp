#include "application.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string> // IWYU pragma: keep

using namespace engine;

double Application::SECONDS_PER_RENDER = 0.0;
double Application::SECONDS_PER_UPDATE = 1.0 / 5000.0;

// clang-format off
const char *Application::FRAME_RATE_OPTIONS[] = {
    "None", "30 FPS", "60 FPS", 
    "75 FPS", "120 FPS","144 FPS", 
    "165 FPS", "240 FPS","360 FPS"
};
// clang-format on

Application::Application()
    : m_window()
{
    Config config = Config::load("config/autoexec.cfg");

    if (config.contains("cl_defaultres") && config.contains("cl_defaultresheight"))
    {
        m_window.set_resolution(config.get<int>("cl_defaultres"), config.get<int>("cl_defaultresheight"));
    }

    if (config.contains("cl_monitor"))
    {
        m_window.set_monitor(config.get<int>("cl_monitor"));
    }

    if (config.contains("cl_displaymode"))
    {
        m_window.set_display_mode((DisplayMode)config.get<int>("cl_displaymode"));
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    m_window.on<FramebufferResizeEvent>([this](FramebufferResizeEvent &e) { on_window_resize(e); });

    m_window.on<KeyPressEvent>([this](KeyPressEvent &e) { on_key_press(e); });

    m_window.on<MouseMoveEvent>([this](MouseMoveEvent &e) { on_mouse_move(e); });

    m_window.on<MouseScrollEvent>([this](MouseScrollEvent &e) { on_mouse_scroll(e); });
}

void Application::run()
{
    glDepthFunc(GL_LESS);

    glfwSwapInterval(m_settings.vsync);

    double current;
    double last;
    double elapsed;

    double render_lag = 0.0;
    double update_lag = 0.0;

    last = current = glfwGetTime();

    while (!glfwWindowShouldClose(m_window))
    {
        m_window.refresh();

        elapsed = (current = glfwGetTime()) - last;

        render_lag += elapsed;
        update_lag += elapsed;

        glfwPollEvents();

        while (update_lag >= SECONDS_PER_UPDATE)
        {
            m_scene.step(SECONDS_PER_UPDATE);
            update_lag -= SECONDS_PER_UPDATE;
        }

        if (render_lag >= SECONDS_PER_RENDER)
        {
            int width, height;
            glfwGetFramebufferSize(m_window, &width, &height);

            // m_renderer.render(width, height);
            m_renderer.render(&m_scene, width, height);

            if (m_debug_flags.show_debug_window)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                if (ImGui::Begin("Streamline Engine Debugger", &m_debug_flags.show_debug_window))
                {
                    if (ImGui::Button("Show metrics"))
                    {
                        m_debug_flags.show_debug_metrics = true;
                    }

                    if (m_debug_flags.show_debug_metrics)
                    {
                        ImGui::ShowMetricsWindow();
                    }

                    for (auto *o : Debugger::objects())
                    {
                        o->on_debug();
                    }

                    ImGui::End();
                }

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            glfwSwapBuffers(m_window);

            render_lag = 0.0;
        }

        last = current;
    }
}

void Application::on_window_resize(FramebufferResizeEvent &e)
{
    m_renderer.on_viewport_resize(e.width, e.height);
    m_scene.on_viewport_resize(e.width, e.height);
}

void Application::on_key_press(KeyPressEvent &e)
{
    if (e.key == GLFW_KEY_GRAVE_ACCENT && e.action == GLFW_PRESS)
    {
        if (e.mods == GLFW_MOD_SHIFT)
        {
            m_window_flags.show_mouse = !m_window_flags.show_mouse;
            if (m_window_flags.show_mouse)
            {
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            m_window_flags.first_mouse = true;
        }
        else
        {
            m_debug_flags.show_debug_window = !m_debug_flags.show_debug_window;
            if (m_debug_flags.show_debug_window)
            {
                m_window_flags.capture_mouse = false;
                if (!m_window_flags.show_mouse)
                {
                    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
                m_window_flags.first_mouse = true;
            }
            else
            {
                if (m_debug_flags.show_debug_metrics)
                {
                    m_debug_flags.show_debug_metrics = false;
                    m_debug_flags.show_debug_window = true;
                }
                else
                {
                    m_window_flags.capture_mouse = true;

                    if (!m_window_flags.show_mouse)
                    {
                        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    }
                }
            }
        }
    }
    // TODO: Handle quit with UI, leave ESC
    else if (e.key == GLFW_KEY_ESCAPE && e.action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    InputManager::instance().register_key_state(e.key, e.scancode, e.action, e.mods);
}

void Application::on_mouse_move(MouseMoveEvent &e)
{
    static float last_x = m_window.width() / 2.0f;
    static float last_y = m_window.height() / 2.0f;

    if (!m_window_flags.capture_mouse)
    {
        return;
    }

    if (m_window_flags.first_mouse)
    {
        last_x = e.x_pos;
        last_y = e.y_pos;
        m_window_flags.first_mouse = false;
    }

    float x_pos = static_cast<float>(e.x_pos);
    float y_pos = static_cast<float>(e.y_pos);

    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;

    last_x = x_pos;
    last_y = y_pos;

    InputManager::instance().register_cursor_event(x_offset, y_offset);
}

void Application::on_mouse_scroll(MouseScrollEvent &e)
{
    if (m_debug_flags.show_debug_window)
    {
        return;
    }

    InputManager::instance().register_scroll_event(e.x_offset, e.y_offset);
}

void Application::on_debug()
{
    if (ImGui::TreeNode("Application"))
    {
        if (ImGui::Combo(
                "Framerate Limit", &m_settings.framerate, FRAME_RATE_OPTIONS, IM_ARRAYSIZE(FRAME_RATE_OPTIONS)))
        {
            auto rate = static_cast<double>(strtol(FRAME_RATE_OPTIONS[m_settings.framerate], NULL, 0));

            if (rate)
            {
                SECONDS_PER_RENDER = 1.0 / (rate);
            }
            else
            {
                SECONDS_PER_RENDER = 0.0;
            }
        }

        if (ImGui::Checkbox("Vertical Sync", (bool *)&m_settings.vsync))
        {
            glfwSwapInterval(m_settings.vsync);
        }

        ImGui::TreePop();
    }
}