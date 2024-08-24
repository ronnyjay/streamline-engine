#pragma once

#include "event.hpp"

class key_event : public event
{
  public:
    key_event(unsigned int gl_key, unsigned int gl_scancode, unsigned int gl_action, unsigned int gl_mods)
        : key(gl_key)
        , scancode(gl_scancode)
        , action(gl_action)
        , mods(gl_mods)
    {
        type_ = KeyEvent;
    }

    unsigned int key;
    unsigned int scancode;
    unsigned int action;
    unsigned int mods;
};