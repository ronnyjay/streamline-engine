#pragma once

#include "event.hpp"

namespace engine
{

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int width, int height)
        : width(width)
        , height(height)
    {
    }

    int width;
    int height;

    EVENT_TYPE(WindowResize)
};

struct KeyEvent : public Event
{
    KeyEvent(int key, int scancode, int action, int mods)
        : key(key)
        , scancode(scancode)
        , action(action)
        , mods(mods)
    {
    }

    int key;
    int scancode;
    int action;
    int mods;

    EVENT_TYPE(KeyPress)
};

} // namespace engine