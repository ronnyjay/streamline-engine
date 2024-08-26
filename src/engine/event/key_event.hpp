#pragma once

#include "event.hpp"

class key_press_event : public event
{
  public:
    STREAMLINE_MAKE_CALLBACK(key_press_event);

    key_press_event(unsigned int gl_key, unsigned int gl_scancode, unsigned int gl_action, unsigned int gl_mods)
        : key(gl_key)
        , scancode(gl_scancode)
        , action(gl_action)
        , mods(gl_mods)
    {
    }

    unsigned int key;
    unsigned int scancode;
    unsigned int action;
    unsigned int mods;

    std::string to_string() const override
    {
        throw unimplemented_exception(std::source_location::current());
    }
};