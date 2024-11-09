#pragma once

#include <functional>

namespace engine
{

// clang-format off
enum class EventType
{
    None,
    WindowResized,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};
// clang-format on

#define EVENT_TYPE(type)                                                                                               \
    static EventType GetStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType GetEventType() const override                                                                    \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }

struct Event
{
    virtual ~Event() = default;

    //
    bool bIsHandled = false;
    //

    static EventType GetStaticType()
    {
        return EventType::None;
    }

    virtual EventType GetEventType() const = 0;
};

typedef std::function<void(Event &&)> EventCallback;

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int width, int height)
        : width(width)
        , height(height)
    {
    }

    const int width;
    const int height;

    EVENT_TYPE(WindowResized)
};

struct KeyPressEvent : public Event
{
    KeyPressEvent(int key, int mods, bool repeat)
        : key(key)
        , mods(mods)
        , bIsRepeat(repeat)
    {
    }

    const int key;
    const int mods;

    const bool bIsRepeat;

    EVENT_TYPE(KeyPressed)
};

struct KeyReleaseEvent : public Event
{
    KeyReleaseEvent(int key)
        : key(key)
    {
    }

    const int key;

    EVENT_TYPE(KeyReleased)
};

struct MouseButtonPressEvent : public Event
{
    MouseButtonPressEvent(int button)
        : button(button)
    {
    }

    const int button;

    EVENT_TYPE(MouseButtonPressed)
};

struct MouseButtonReleaseEvent : public Event
{
    MouseButtonReleaseEvent(int button)
        : button(button)
    {
    }

    const int button;

    EVENT_TYPE(MouseButtonReleased)
};

struct MouseMoveEvent : public Event
{
    MouseMoveEvent(double xpos, double ypos)
        : xpos(xpos)
        , ypos(ypos)
    {
    }

    const double xpos;
    const double ypos;

    EVENT_TYPE(MouseMoved)
};

struct MouseScrollEvent : public Event
{
    MouseScrollEvent(double xoffset, double yoffset)
        : xoffset(xoffset)
        , yoffset(yoffset)
    {
    }

    const double xoffset;
    const double yoffset;

    EVENT_TYPE(MouseScrolled)
};

class EventDispatcher
{
  public:
    EventDispatcher(Event &event)
        : mEvent(event)
    {
    }

    template <typename T, typename F, typename C>
    bool Dispatch(C *instance, const F &func)
    {
        if (mEvent.GetEventType() == T::GetStaticType())
        {
            mEvent.bIsHandled |= (instance->*func)(static_cast<T &>(mEvent));
            return true;
        }
        return false;
    }

  private:
    Event &mEvent;
};

} // namespace engine