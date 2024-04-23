#include <engine/debugger/debugger.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace engine;

debugger::debugger() : m_metrics(false), m_enabled(true)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

void debugger::initialize(GLFWwindow *window)
{
    // Setup Platform/Renderer backends
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void debugger::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (m_enabled)
    {
        ImGui::Begin("Streamline Engine Debugger");

        if (ImGui::Button("Show Metrics"))
        {
            m_metrics = !m_metrics;
        }

        render_node_table(m_nodes);

        if (m_metrics)
        {
            ImGui::ShowMetricsWindow();
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void debugger::render_node_table(debug_node_table &table)
{
    for (auto node_it = table.begin(); node_it != table.end(); ++node_it)
    {
        if (ImGui::TreeNode(node_it->first.c_str()))
        {
            for (auto it = node_it->second.toggles().begin(); it != node_it->second.toggles().end(); ++it)
            {
                if (ImGui::Checkbox(it->first.c_str(), &it->second.first))
                {
                    it->second.second(it->second.first);
                }
            }

            for (auto it = node_it->second.buttons().begin(); it != node_it->second.buttons().end(); ++it)
            {
                ImGui::TextUnformatted(it->first.c_str());
                ImGui::SameLine();
                if (ImGui::Button(it->second.first->c_str()))
                {
                    it->second.second();
                }
            }

            for (auto it = node_it->second.sliders().begin(); it != node_it->second.sliders().end(); ++it)
            {
                ImGui::DragFloat(it->first.c_str(), it->second.first);
                it->second.second();
            }

            render_node_table(node_it->second.children());

            ImGui::TreePop();
        }
    }
}

// void debugger::add_node(std::string node)
// {
//     m_nodes.emplace(node, debug_button{});
// }

// void debugger::pop_node(std::string node)
// {
//     if (m_nodes.contains(node))
//     {
//         m_nodes.erase(node);
//     }
// }

debugger::~debugger()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}