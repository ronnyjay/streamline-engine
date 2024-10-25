#pragma once

#include "event.hpp"

namespace engine
{

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int width, int height)
        : Width(width)
        , Height(height)
    {
    }

    int Width;
    int Height;

    EVENT_TYPE(WindowResized)
};

struct KeyPressEvent : public Event
{
    KeyPressEvent(int key, int mods, bool repeat)
        : Key(key)
        , Mods(mods)
        , bIsRepeat(repeat)
    {
    }

    int  Key;
    int  Mods;

    bool bIsRepeat;

    EVENT_TYPE(KeyPressed)
};

struct KeyReleaseEvent : public Event
{
    KeyReleaseEvent(int key)
        : Key(key)
    {
    }

    int Key;

    EVENT_TYPE(KeyReleased)
};

struct MouseButtonPressEvent : public Event
{
    MouseButtonPressEvent(int button, int mods)
        : Button(button)
        , Mods(mods)
    {
    }

    int Button;
    int Mods;

    EVENT_TYPE(MouseButtonPressed)
};

struct MouseButtonReleaseEvent : public Event
{
    MouseButtonReleaseEvent(int button)
        : Button(button)
    {
    }

    int Button;

    EVENT_TYPE(MouseButtonReleased)
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

struct MouseScrollEvent : public Event
{
    MouseScrollEvent(double xOffset)
        : xOffset(xOffset)
    {
    }

    double xOffset;

    EVENT_TYPE(MouseScrolled)
};

} // namespace engine