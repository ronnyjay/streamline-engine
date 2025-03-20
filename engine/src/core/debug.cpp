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