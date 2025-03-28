#include "core/debug.hpp"
#include "core/application.hpp"
#include "core/renderer.hpp"
#include "core/window.hpp"

#include <assimp/types.h>
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
                Application::getInstance().getWindow()->close();
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
        bool showWireframes = Application::getInstance().getRenderer()->flags.b_showWireframes;
        if (ImGui::Checkbox("Show wireframes", &showWireframes))
        {
            Application::getInstance().getRenderer()->flags.b_showWireframes = showWireframes;
        }

        bool showCollisions = Application::getInstance().getRenderer()->flags.b_showCollisions;
        if (ImGui::Checkbox("Show collisions", &showCollisions))
        {
            Application::getInstance().getRenderer()->flags.b_showCollisions = showCollisions;
        }

        ImGui::TreePop();
    }
}

void DebugWindow::drawVideoSettings()
{
    if (ImGui::TreeNode("Video"))
    {
        WindowMode windowMode = Application::getInstance().getWindow()->getWindowMode();

        if (windowMode == WindowMode::Windowed)
        {
            ImGui::BeginDisabled();
        }

        // Monitor select

        if (windowMode == WindowMode::Windowed)
        {
            ImGui::EndDisabled();
        }

        if (windowMode == WindowMode::WindowedFullscreen)
        {
            ImGui::BeginDisabled();
        }

        // Resolution select

        if (windowMode == WindowMode::WindowedFullscreen)
        {
            ImGui::EndDisabled();
        }

        if (ImGui::Combo("Display Mode", (int *)&windowMode, DisplayModes, IM_ARRAYSIZE(DisplayModes)))
        {
            Application::getInstance().getWindow()->setWindowMode(windowMode);
        }

        // Frame Rate Limit

        // Vertical Sync
        if (ImGui::Checkbox("Vertical Sync", &m_videoSettings.b_verticalSync))
        {
            Application::getInstance().getRenderer()->enableVsync(m_videoSettings.b_verticalSync);
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