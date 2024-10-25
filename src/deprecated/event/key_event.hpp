#pragma once

#include "event.hpp"

class key_pressed_event : public event
{
  public:
    key_pressed_event(unsigned int k, unsigned int s, unsigned int a, unsigned int m)
        : key(k)
        , scancode(s)
        , action(a)
        , mods(m)
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