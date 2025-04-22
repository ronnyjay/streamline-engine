#pragma once

#include <cstdint>
#include <functional>

namespace engine
{

// clang-format off
enum class EventType : std::uint8_t
{
    NONE,
    KEY_PRESSED, KEY_RELEASED,
    WINDOW_RESIZED, WINDOW_MINIMIZED, WINDOW_MAXIMIZED,
    MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_BUTTON_MOVED, MOUSE_BUTTON_SCROLLED
};
// clang-format on

#define EVENT_TYPE(type)                                                                                               \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType getType() const override                                                                         \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }

struct Event
{
    virtual ~Event() = default;

    //
    bool b_isHandled = false;
    //

    static EventType getStaticType()
    {
        return EventType::NONE;
    }

    [[nodiscard]] virtual EventType getType() const = 0;
};

struct WindowResizeEvent : public Event
{
    WindowResizeEvent(int width, int height)
        : width(width)
        , height(height)
    {
    }

    int width;
    int height;

    EVENT_TYPE(WINDOW_RESIZED)
};

struct WindowMaximizeEvent : public Event
{
    WindowMaximizeEvent(bool maximized)
        : maximized(maximized)
    {
    }

    bool maximized;

    EVENT_TYPE(WINDOW_MAXIMIZED)
};

struct WindowMinimizeEvent : public Event
{
    WindowMinimizeEvent(bool minimized)
        : minimized(minimized)
    {
    }

    bool minimized;

    EVENT_TYPE(WINDOW_MINIMIZED)
};

struct KeyPressEvent : public Event
{
    KeyPressEvent(int key, int mods, bool repeat)
        : key(key)
        , mods(mods)
        , repeat(repeat)
    {
    }

    int  key;
    int  mods;
    bool repeat;

    EVENT_TYPE(KEY_PRESSED)
};

struct KeyReleaseEvent : public Event
{
    explicit KeyReleaseEvent(int key)
        : key(key)
    {
    }

    int key;

    EVENT_TYPE(KEY_RELEASED)
};

struct MouseButtonPressEvent : public Event
{
    explicit MouseButtonPressEvent(int button)
        : button(button)
    {
    }

    int button;

    EVENT_TYPE(MOUSE_BUTTON_PRESSED)
};

struct MouseButtonReleaseEvent : public Event
{
    explicit MouseButtonReleaseEvent(int button)
        : button(button)
    {
    }

    int button;

    EVENT_TYPE(MOUSE_BUTTON_RELEASED)
};

struct MouseMoveEvent : public Event
{
    MouseMoveEvent(double xpos, double ypos)
        : xpos(xpos)
        , ypos(ypos)
    {
    }

    double xpos;
    double ypos;

    EVENT_TYPE(MOUSE_BUTTON_MOVED)
};

struct MouseScrollEvent : public Event
{
    MouseScrollEvent(double xoffset, double yoffset)
        : xoffset(xoffset)
        , yoffset(yoffset)
    {
    }

    double xoffset;
    double yoffset;

    EVENT_TYPE(MOUSE_BUTTON_SCROLLED)
};

class EventDispatcher
{
  public:
    explicit EventDispatcher(Event &event)
        : event(event)
    {
    }

    template <typename T, typename F>
    bool dispatch(const F &&func)
    {
        if (event.getType() == T::getStaticType())
        {
            event.b_isHandled |= func(static_cast<T &>(event));
            return true;
        }
        return false;
    }

    template <typename T, typename F, typename C>
    bool dispatch(C *instance, const F &func)
    {
        if (event.getType() == T::getStaticType())
        {
            event.b_isHandled |= (instance->*func)(static_cast<T &>(event));
            return true;
        }
        return false;
    }

  private:
    Event &event;
};

using EventCallback = std::function<void(Event &&)>;

} // namespace engine