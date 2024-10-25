#pragma once

#include "event.hpp"

class mouse_button_pressed_event : public event
{
  public:
    mouse_button_pressed_event(int button, int action, int mods)
        : m_button(button)
        , m_action(action)
        , m_mods(mods)
    {
    }

    int button() const
    {
        return m_button;
    }

    int action() const
    {
        return m_action;
    }

    int mods() const
    {
        return m_mods;
    }

    std::string to_string() const override
    {
        return (std::stringstream() << "Mouse Pressed: " << m_button << ", " << m_action << ", " << m_mods).str();
    }

  private:
    int m_button;
    int m_action;
    int m_mods;
};

class mouse_moved_event : public event
{
  public:
    mouse_moved_event(double xpos_in, double ypos_in)
    {
        x_offset = xpos_in;
        y_offset = ypos_in;
    }

    double x_offset;
    double y_offset;

    std::string to_string() const override
    {
        return (std::stringstream() << "Mouse moved: " << x_offset << ", " << y_offset).str();
    }
};

class mouse_scrolled_event : public event
{
  public:
    mouse_scrolled_event(double yoffset)
    {
    }

    double yoffset;

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }
};