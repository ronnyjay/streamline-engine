#include "core/debug.hpp"
#include "core/application.hpp"

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
    if (showDebugWindow)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Streamline Engine Debugger", &showDebugWindow))
        {
            if (ImGui::Button("Show metrics"))
            {
                showDebugMetrics = true;
            }

            if (showDebugMetrics)
            {
                ImGui::ShowMetricsWindow();
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

DebugWindow::~DebugWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}