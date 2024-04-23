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

        render(m_nodes);

        if (m_metrics)
        {
            ImGui::ShowMetricsWindow();
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void debugger::render(debug_node_table &table)
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

            render(node_it->second.children());

            ImGui::TreePop();
        }
    }
}

void debugger::add_child_node(std::string parent, std::string child, debug_node_table &table)
{
    // add child if it's contained in the node table
    if (table.contains(parent))
    {
        table.at(parent).add_child(child);
        return;
    }

    // recursively search through all node tables
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        add_child_node(parent, child, it->second.children());
    }
}

void debugger::add_toggle(std::string node, std::string toggle, bool value, std::function<void(bool)> callback, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).add_toggle(toggle, value, callback);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        add_toggle(node, toggle, value, callback, it->second.children());
    }
}

void debugger::add_button(std::string node, std::string button, std::string *value, std::function<void()> callback, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).add_button(button, value, callback);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        add_button(node, button, value, callback, it->second.children());
    }
}

void debugger::add_slider(std::string node, std::string slider, float *pointer, std::function<void()> callback, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).add_slider(slider, pointer, callback);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        add_slider(node, slider, pointer, callback, it->second.children());
    }
}

void debugger::pop_node(std::string node, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.erase(node);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        pop_node(node, it->second.children());
    }
}

void debugger::pop_toggle(std::string node, std::string toggle, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).pop_toggle(toggle);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        pop_toggle(node, toggle, it->second.children());
    }
}

void debugger::pop_button(std::string node, std::string button, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).pop_button(button);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        pop_button(node, button, it->second.children());
    }
}

void debugger::pop_slider(std::string node, std::string slider, debug_node_table &table)
{
    if (table.contains(node))
    {
        table.at(node).pop_slider(slider);
    }

    for (auto it = table.begin(); it != table.end(); ++it)
    {
        pop_slider(node, slider, it->second.children());
    }
}

debugger::~debugger()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}