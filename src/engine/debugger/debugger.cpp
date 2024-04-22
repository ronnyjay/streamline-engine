#include <engine/debugger/debugger.hpp>
#include <stdexcept>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace engine;

debugger::debugger() : m_enabled(true)
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

        for (auto node_it = m_nodes.begin(); node_it != m_nodes.end(); ++node_it)
        {
            if (ImGui::TreeNode(node_it->first.c_str()))
            {
                for (auto opt_it = node_it->second.begin()->begin(); opt_it != node_it->second.begin()->end(); ++opt_it)
                {
                    ImGui::TextUnformatted(opt_it->first.c_str());
                    ImGui::SameLine();

                    if (ImGui::Checkbox(" ", &opt_it->second.first))
                    {
                        opt_it->second.second(opt_it->second.first);
                    }
                }

                ImGui::TreePop();
            }
        }

        if (m_metrics)
        {
            ImGui::ShowMetricsWindow();
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void debugger::add_node(std::string node)
{
    m_nodes.emplace(node, std::vector<debug_option>{});
}

void debugger::remove_node(std::string node)
{
    if (m_nodes.find(node) == m_nodes.end())
    {
        return;
    }

    m_nodes.erase(node);
}

void debugger::add_option(std::string node, std::string option, bool value, std::function<void(bool)> callback)
{
    auto node_iterator = m_nodes.find(node);

    if (node_iterator == m_nodes.end())
    {
        throw std::runtime_error("Unable to add Debug Option. Node does not exist");
    }

    debug_option opt;
    opt.emplace(option, std::make_pair(value, callback));

    node_iterator->second.emplace_back(opt);
}

void debugger::remove_option(std::string node, std::string option)
{
}

debugger::~debugger()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}