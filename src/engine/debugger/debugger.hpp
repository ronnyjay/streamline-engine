#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

namespace engine
{

class debug_node;

typedef std::unordered_map<std::string, std::pair<bool, std::function<void(bool)>>> debug_toggle_table;
typedef std::unordered_map<std::string, std::pair<std::string *, std::function<void()>>> debug_button_table;
typedef std::unordered_map<std::string, std::pair<float *, std::function<void()>>> debug_slider_table;
typedef std::unordered_map<std::string, debug_node> debug_node_table;

class debug_node
{
  public:
    debug_node()
    {
    }

    void add_toggle(std::string toggle, bool value, std::function<void(bool)> callback)
    {
        m_toggles.emplace(toggle, std::make_pair(value, callback));
    }

    void add_button(std::string button, std::string *value, std::function<void()> callback)
    {
        m_buttons.emplace(button, std::make_pair(value, callback));
    }

    void add_slider(std::string slider, float *pointer, std::function<void()> callback)
    {
        m_sliders.emplace(slider, std::make_pair(pointer, callback));
    }

    void add_child(std::string child)
    {
        m_children.emplace(child, debug_node{});
    }

    void pop_toggle(std::string toggle)
    {
        if (m_toggles.contains(toggle))
        {
            m_toggles.erase(toggle);
        }
    }

    void pop_button(std::string button)
    {
        if (m_buttons.contains(button))
        {
            m_buttons.erase(button);
        }
    }

    void pop_slider(std::string slider)
    {
        if (m_sliders.contains(slider))
        {
            m_sliders.erase(slider);
        }
    }

    debug_toggle_table &toggles()
    {
        return m_toggles;
    }

    debug_button_table &buttons()
    {
        return m_buttons;
    }

    debug_slider_table &sliders()
    {
        return m_sliders;
    }

    debug_node_table &children()
    {
        return m_children;
    }

  private:
    debug_toggle_table m_toggles;
    debug_button_table m_buttons;
    debug_slider_table m_sliders;
    debug_node_table m_children;
};

class debugger
{
  public:
    debugger();

    void initialize(GLFWwindow *);
    void render();

    void add_node(std::string node)
    {
        m_nodes.emplace(node, debug_node{});
    }

    void add_child_node(std::string parent, std::string child)
    {
        if (m_nodes.contains(parent))
        {
            m_nodes.at(parent).add_child(child);
        }
    }

    void pop_node(std::string node)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.erase(node);
        }
    }

    void add_toggle(std::string node, std::string toggle, bool value, std::function<void(bool)> callback)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.at(node).toggles().emplace(toggle, std::make_pair(value, callback));
        }

        for (auto node_it = m_nodes.begin(); node_it != m_nodes.end(); ++node_it)
        {
            if (node_it->second.children().contains(node))
            {
                node_it->second.children().at(node).add_toggle(toggle, value, callback);
            }
        }
    }

    void add_button(std::string node, std::string button, std::string *value, std::function<void()> callback)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.at(node).add_button(button, value, callback);
        }

        for (auto node_it = m_nodes.begin(); node_it != m_nodes.end(); ++node_it)
        {
            if (node_it->second.children().contains(node))
            {
                node_it->second.children().at(node).add_button(button, value, callback);
            }
        }
    }

    void add_slider(std::string node, std::string slider, float *pointer, std::function<void()> callback)
    {
        debug_node found_node;

        if (m_nodes.contains(node))
        {
            m_nodes.at(node).add_slider(slider, pointer, callback);
        }

        for (auto node_it = m_nodes.begin(); node_it != m_nodes.end(); ++node_it)
        {
            if (node_it->second.children().contains(node))
            {
                node_it->second.children().at(node).add_slider(slider, pointer, callback);
            }
        }
    }

    void pop_toggle(std::string node, std::string toggle)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.at(node).pop_toggle(toggle);
        }
    }

    void pop_button(std::string node, std::string button)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.at(node).pop_button(button);
        }
    }

    void pop_slider(std::string node, std::string slider)
    {
        if (m_nodes.contains(node))
        {
            m_nodes.at(node).pop_slider(slider);
        }
    }

    void enable(bool enabled)
    {
        m_enabled = enabled;
    }

    void toggle()
    {
        m_enabled = !m_enabled;
    }

    ~debugger();

  private: // default options
    bool m_metrics;

  private:
    void render_node_table(debug_node_table &);

  private:
    bool m_enabled;

    std::unordered_map<std::string, debug_node> m_nodes;
};

}; // namespace engine