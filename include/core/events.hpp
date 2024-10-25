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

} // namespace engine