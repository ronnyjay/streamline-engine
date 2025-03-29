#include "core/debug.hpp"
#include "core/application.hpp"
#include "core/renderer.hpp"
#include "core/resolution.hpp"
#include "core/window.hpp"
#include "subsystems/display_manager.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace engine;

DebugWindow::DebugWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplGlfw_InitForOpenGL(Application::getInstance().getWindow()->operator GLFWwindow *(), true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void DebugWindow::draw()
{
    if (b_showWindow)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Streamline Engine Debugger", &b_showWindow))
        {
            if (ImGui::Button("Show metrics"))
            {
                b_showMetrics = true;
            }

            if (b_showMetrics)
            {
                ImGui::ShowMetricsWindow();
            }

            drawDebugSettings();
            drawVideoSettings();
            drawSceneSettings();

            if (ImGui::Button("Exit"))
            {
                Window::getInstance().close();
            }
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

DebugWindow::~DebugWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void DebugWindow::drawDebugSettings()
{
    if (ImGui::TreeNode("Debug"))
    {
        bool showWireframes = Renderer::getInstance().flags.b_showWireframes;
        if (ImGui::Checkbox("Show wireframes", &showWireframes))
        {
            Renderer::getInstance().flags.b_showWireframes = showWireframes;
        }

        bool showCollisions = Renderer::getInstance().flags.b_showCollisions;
        if (ImGui::Checkbox("Show collisions", &showCollisions))
        {
            Renderer::getInstance().flags.b_showCollisions = showCollisions;
        }

        ImGui::TreePop();
    }
}

void DebugWindow::drawVideoSettings()
{
    if (ImGui::TreeNode("Video"))
    {
        WindowMode windowMode = Window::getInstance().getWindowMode();

        if (windowMode == WindowMode::Windowed)
        {
            ImGui::BeginDisabled();
        }

        std::vector<std::unique_ptr<Monitor>> &monitors =
            const_cast<std::vector<std::unique_ptr<Monitor>> &>(DisplayManager::getInstance().getMonitors());

        ImGui::Combo(
            "Monitor", &m_videoSettings.monitorIndex,
            [](void *data, int index, const char **text) -> bool
            {
                auto &vector = *static_cast<std::vector<Monitor *> *>(data);

                if (index < 0 || index >= static_cast<int>(vector.size()))
                {
                    return false;
                }
                *text = vector[index]->title;

                return true;
            },
            static_cast<void *>(&monitors), monitors.size());

        if (windowMode == WindowMode::Windowed)
        {
            ImGui::EndDisabled();
        }

        Monitor *currentMonitor = DisplayManager::getInstance().getCurrentMonitor();

        if (ImGui::Combo(
                "Resolution", &m_videoSettings.resolutionIndex,
                [](void *data, int index, const char **text) -> bool
                {
                    auto &vector = *static_cast<std::vector<Resolution> *>(data);

                    if (index < 0 || index >= static_cast<int>(vector.size()))
                    {
                        return false;
                    }
                    *text = vector[index].c_str();

                    return true;
                },
                static_cast<void *>(&currentMonitor->resolutions), currentMonitor->resolutions.size()))
        {
            Resolution res = currentMonitor->resolutions[m_videoSettings.resolutionIndex];

            if (windowMode == WindowMode::Windowed || windowMode == WindowMode::WindowedFullscreen)
            {
                float sizeX = res.width / currentMonitor->scaleX;
                float sizeY = res.height / currentMonitor->scaleY;

                Window::getInstance().resize(sizeX, sizeY);

                float positionX = (currentMonitor->width - res.width) / 2.0;
                float positionY = (currentMonitor->height - res.height) / 2.0;

                Window::getInstance().moveTo(positionX, positionY);
            }

            Renderer::getInstance().onWindowResize(res.width, res.height);
        }

        if (ImGui::Combo("Display Mode", (int *)&windowMode, DisplayModes, IM_ARRAYSIZE(DisplayModes)))
        {
            Window::getInstance().setWindowMode(windowMode);

            Resolution res = currentMonitor->resolutions[m_videoSettings.resolutionIndex];

            if (windowMode == WindowMode::Windowed || windowMode == WindowMode::WindowedFullscreen)
            {
                float sizeX = res.width / currentMonitor->scaleX;
                float sizeY = res.height / currentMonitor->scaleY;

                Window::getInstance().resize(sizeX, sizeY);

                float positionX = (currentMonitor->width - res.width) / 2.0;
                float positionY = (currentMonitor->height - res.height) / 2.0;

                Window::getInstance().moveTo(positionX, positionY);
            }

            Renderer::getInstance().onWindowResize(res.width, res.height);
        }

        // Frame Rate Limit
        // ...

        if (ImGui::Checkbox("Vertical Sync", &m_videoSettings.b_verticalSync))
        {
            Renderer::getInstance().enableVsync(m_videoSettings.b_verticalSync);
        }

        ImGui::TreePop();
    }
}

void DebugWindow::drawSceneSettings()
{
    if (ImGui::TreeNode("Scene"))
    {
        ImGui::TreePop();
    }
}
