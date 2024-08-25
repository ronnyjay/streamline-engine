#pragma once

#include <set>

#include <glm/ext/matrix_clip_space.hpp>

#include <engine/user_interface/ui_element.hpp>

namespace engine
{

class user_interface
{
  public:
    user_interface()
    {}

    ~user_interface()
    {}

    virtual void render()
    {
        for (auto element : m_elements)
        {
            element->render();
        }
    }

    void add_element(ui_element *element)
    {
        m_elements.insert(element);
    }

    void remove_element(ui_element *element)
    {
        m_elements.erase(element);
    }

    void mouse_pos(const float x, const float y)
    {
        for (auto &elmnt : m_elements)
        {
            bool hovering = elmnt->is_point_inside(x, y);
            elmnt->hover(hovering);
        }
    }

    void mouse_press(const int button, int action, const float x, const float y)
    {
        for (auto &elmnt : m_elements)
        {
            if (elmnt->is_point_inside(x, y))
                elmnt->click(button, action);
        }
    }

    void set_dimensions(const unsigned int width, const unsigned int height)
    {
        float ar = float(width) / float(height);
        auto o = glm::ortho(-ar, ar, -1.0f, 1.0f, 0.1f, 100.0f);
        for (auto &elmnt : m_elements)
        {
            elmnt->set_projection(o);
        }
    }

  protected:
    std::set<ui_element*> m_elements;

    
};

};
