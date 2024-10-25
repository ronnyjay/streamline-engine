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

    EVENT_TYPE(WindowResized)
};

struct KeyPressEvent : public Event
{
    KeyPressEvent(int key, int scancode, int action, int mods)
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

    EVENT_TYPE(KeyPressed)
};

struct MouseMoveEvent : public Event
{
    MouseMoveEvent(double xOffset, double yOffset)
        : xOffset(xOffset)
        , yOffset(yOffset)
    {
    }

    double xOffset;
    double yOffset;

    EVENT_TYPE(MouseMoved);
};

} // namespace engine