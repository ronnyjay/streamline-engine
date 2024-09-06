#pragma once

#include <functional>

namespace engine
{

typedef enum EventType
{
    WINDOW_RESIZED,
    KEY_PRESSED,
    MOUSE_PRESSED,
    MOUSE_MOVED,
    MOUSE_SCROLLED
} EventType;

struct Event
{
    virtual ~Event() = default;
};

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int _width, int _height)
        : width(_width)
        , height(_height)
    {
    }

    int width;
    int height;

    static EventType type()
    {
        return WINDOW_RESIZED;
    }
};

struct KeyPressedEvent : public Event
{
    KeyPressedEvent(int _key, int _scancode, int _action, int _mods)
        : key(_key)
        , scancode(_scancode)
        , action(_action)
        , mods(_mods)
    {
    }

    int key;
    int scancode;
    int action;
    int mods;

    static EventType type()
    {
        return KEY_PRESSED;
    }
};

struct MousePressedEvent : public Event
{
    MousePressedEvent(int _button, int _action, int _mods)
        : button(_button)
        , action(_action)
        , mods(_mods)
    {
    }

    int button;
    int action;
    int mods;

    static EventType type()
    {
        return MOUSE_PRESSED;
    }
};

struct MouseMovedEvent : public Event
{
    MouseMovedEvent(double _xpos, double _ypos)
        : xpos(_xpos)
        , ypos(_ypos)
    {
    }

    double xpos;
    double ypos;

    static EventType type()
    {
        return MOUSE_MOVED;
    }
};

struct MouseScrolledEvent : public Event
{
    MouseScrolledEvent(double _xoffset, double _yoffset)
        : xoffset(_xoffset)
        , yoffset(_yoffset)
    {
    }

    double xoffset;
    double yoffset;

    static EventType type()
    {
        return MOUSE_SCROLLED;
    }
};

typedef std::function<void(Event &)> EventCallback;

class EventDispatcher
{
  public:
    ~EventDispatcher() = default;

    template <typename T>
    void on(std::function<void(T &)> fn)
    {
        m_events[T::type()] = [fn](Event &e)
        {
            fn(static_cast<T &>(e));
        };
    }

  protected:
    void dispatch(EventType type, Event &&e)
    {
        auto it = m_events.find(type);

        if (it != m_events.end())
        {
            it->second(e);
        }
    }

  private:
    std::unordered_map<EventType, EventCallback> m_events;
};

} // namespace engine