#include "core/debug.hpp"
#include "core/application.hpp"
#include "core/resolution.hpp"
#include "core/settings.hpp"
#include "core/window.hpp"
#include "renderer/renderer.hpp"
#include "subsystems/display_manager.hpp"

#include <cstddef>
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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (b_showWindow)
    {
        if (ImGui::Begin("Streamline Engine Debugger", &b_showWindow))
        {
            b_windowShown = true;

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
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (b_windowShown && !b_showWindow)
    {
        if (UserSettings::getInstance().hasUnsavedChanges())
        {
            UserSettings::getInstance().discard();
        }

        b_windowShown = false;
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
        WindowMode windowMode = UserSettings::getInstance().getWindowMode();

        if (windowMode == WindowMode::Windowed)
        {
            ImGui::BeginDisabled();
        }

        std::vector<std::unique_ptr<Monitor>> &monitors =
            const_cast<std::vector<std::unique_ptr<Monitor>> &>(DisplayManager::getInstance().getMonitors());

        int monitorIndex = UserSettings::getInstance().getPrimaryMonitor();

        ImGui::Combo(
            "Monitor", &monitorIndex,
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

        Monitor *currentMonitor  = DisplayManager::getInstance().getCurrentMonitor();

        int      resolutionIndex = -1;

        for (size_t i = 0; i < currentMonitor->resolutions.size(); i++)
        {
            if (UserSettings::getInstance().getResolution() == currentMonitor->resolutions[i])
            {
                resolutionIndex = i;
            }
        }

        if (ImGui::Combo(
                "Resolution", &resolutionIndex,
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
            UserSettings::getInstance().setResolution(currentMonitor->resolutions[resolutionIndex]);
        }

        if (ImGui::Combo("Display Mode", (int *)&windowMode, DisplayModes, IM_ARRAYSIZE(DisplayModes)))
        {
            UserSettings::getInstance().setWindowMode(windowMode);
        }

        // Frame Rate Limit
        // ...

        bool verticalSync = UserSettings::getInstance().getVerticalSync();

        if (ImGui::Checkbox("Vertical Sync", &verticalSync))
        {
            UserSettings::getInstance().setVerticalSync(verticalSync);
        }

        if (ImGui::Button("Apply"))
        {
            UserSettings::getInstance().apply();
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
