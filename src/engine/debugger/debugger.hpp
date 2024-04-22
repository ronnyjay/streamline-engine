#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <unordered_map>

namespace engine
{

typedef std::unordered_map<std::string, std::pair<bool, std::function<void(bool)>>> debug_option;
typedef std::unordered_map<std::string, std::vector<debug_option>> debug_node;

class debugger
{
  public:
    debugger();

    void initialize(GLFWwindow *);
    void render();

    void add_node(std::string);
    void remove_node(std::string);

    void add_option(std::string, std::string, bool, std::function<void(bool)>);
    void remove_option(std::string, std::string);

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
    bool m_enabled;

    debug_node m_nodes;
    debug_option m_options;
};

}; // namespace engine