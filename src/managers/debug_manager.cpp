#include "managers/debug_manager.hpp"

#include "core/application.hpp"
#include "core/event.hpp"

using namespace engine;

//
extern Application gApplication;
//

void DebugManager::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplGlfw_InitForOpenGL(*gApplication.GetWindow(), true);

    // Automatically determine GLSL version
    ImGui_ImplOpenGL3_Init(nullptr);
}

void DebugManager::DeInit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void DebugManager::Draw()
{
    if (mShowDebugWindow)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Streamline Engine", &mShowDebugWindow))
        {
            if (ImGui::Button("Show metrics"))
            {
                mShowDebugMetrics = true;
            }

            if (mShowDebugMetrics)
            {
                ImGui::ShowMetricsWindow();
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void DebugManager::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<KeyPressEvent>(this, &DebugManager::OnKeyPress);
}

bool DebugManager::OnKeyPress(KeyPressEvent &e)
{
    if (e.key == GLFW_KEY_GRAVE_ACCENT)
    {
        mShowDebugWindow = !mShowDebugWindow;

        if (mShowDebugWindow)
        {
        }
        else
        {
        }
    }

    return true;
}
