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

    debug_node &copy_from(const debug_node &node)
    {
        if (this != &node)
        {
            m_toggles = node.m_toggles;
            m_buttons = node.m_buttons;
            m_sliders = node.m_sliders;
            m_children = node.m_children;
        }

        return *this;
    }

    debug_node &operator=(const debug_node &node)
    {
        return copy_from(node);
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

    void add_child(std::string child, debug_node &node)
    {
        m_children.emplace(child, node);
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
        add_child_node(parent, child, m_nodes);
    }

    void add_child_node(std::string parent, std::string child, debug_node &node)
    {
        add_child_node(parent, child, node, m_nodes);
    }

    void add_toggle(std::string node, std::string toggle, bool value, std::function<void(bool)> callback)
    {
        add_toggle(node, toggle, value, callback, m_nodes);
    }

    void add_button(std::string node, std::string button, std::string *value, std::function<void()> callback)
    {
        add_button(node, button, value, callback, m_nodes);
    }

    void add_slider(std::string node, std::string slider, float *pointer, std::function<void()> callback)
    {
        add_slider(node, slider, pointer, callback, m_nodes);
    }

    void pop_node(std::string node)
    {
        pop_node(node, m_nodes);
    }

    void pop_toggle(std::string node, std::string toggle)
    {
        pop_toggle(node, toggle, m_nodes);
    }

    void pop_button(std::string node, std::string button)
    {
        pop_button(node, button, m_nodes);
    }

    void pop_slider(std::string node, std::string slider)
    {
        pop_slider(node, slider, m_nodes);
    }

    void move_node(std::string new_parent, std::string node)
    {
        move_node(new_parent, node, m_nodes);
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

  private: // helper functions
    void render(debug_node_table &);

    void add_child_node(std::string parent, std::string child, debug_node_table &node_table);
    void add_child_node(std::string parent, std::string child, debug_node &node, debug_node_table &node_table);
    void add_toggle(std::string node, std::string toggle, bool value, std::function<void(bool)> callback, debug_node_table &table);
    void add_button(std::string node, std::string button, std::string *value, std::function<void()> callback, debug_node_table &table);
    void add_slider(std::string node, std::string slider, float *pointer, std::function<void()> callback, debug_node_table &table);
    void pop_node(std::string node, debug_node_table &table);
    void pop_toggle(std::string node, std::string toggle, debug_node_table &table);
    void pop_button(std::string node, std::string button, debug_node_table &table);
    void pop_slider(std::string node, std::string slider, debug_node_table &table);
    void move_node(std::string new_parent, std::string node, debug_node_table &table);

  private:
    bool m_enabled;

    debug_node_table m_nodes;
};

}; // namespace engine