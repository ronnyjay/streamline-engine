#pragma once

#include "event.hpp"

class mouse_move_event : public event
{
  public:
    STREAMLINE_MAKE_CALLBACK(mouse_move_event);

    mouse_move_event(double xpos_in, double ypos_in)
    {
    }

    double x_offset;
    double y_offset;

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }
};

class mouse_click_event : public event
{
  public:
    STREAMLINE_MAKE_CALLBACK(mouse_click_event);

    mouse_click_event(int button, int action, int mods)
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
        throw unimplemented_exception(std::source_location::current());
    }

  private:
    int m_button;
    int m_action;
    int m_mods;
};

class mouse_scroll_event : public event
{
  public:
    STREAMLINE_MAKE_CALLBACK(mouse_scroll_event);

    mouse_scroll_event(double yoffset)
    {
    }

    double yoffset;

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }
};