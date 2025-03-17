#pragma once

#include <functional>

namespace engine
{

// clang-format off
enum class event_type
{
    NONE,
    WINDOW_RESIZED,
    KEY_PRESSED, KEY_RELEASED,
    MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_BUTTON_MOVED, MOUSE_BUTTON_SCROLLED
};
// clang-format on

#define EVENT_TYPE(type)                                                                                               \
    static event_type get_static_type()                                                                                \
    {                                                                                                                  \
        return event_type::type;                                                                                       \
    }                                                                                                                  \
    virtual event_type get_type() const override                                                                       \
    {                                                                                                                  \
        return get_static_type();                                                                                      \
    }

struct event
{
    virtual ~event() = default;

    //
    bool b_isHandled = false;
    //

    static event_type get_static_type()
    {
        return event_type::NONE;
    }

    virtual event_type get_type() const = 0;
};

struct window_resize_event : public event
{
    window_resize_event(int width, int height)
        : width(width)
        , height(height)
    {
    }

    const int width;
    const int height;

    EVENT_TYPE(WINDOW_RESIZED)
};

struct key_press_event : public event
{
    key_press_event(int key, int mods, bool repeat)
        : key(key)
        , mods(mods)
        , repeat(repeat)
    {
    }

    const int key;
    const int mods;

    const bool repeat;

    EVENT_TYPE(KEY_PRESSED)
};

struct key_release_event : public event
{
    key_release_event(int key)
        : key(key)
    {
    }

    const int key;

    EVENT_TYPE(KEY_RELEASED)
};

struct mouse_button_press_event : public event
{
    mouse_button_press_event(int button)
        : button(button)
    {
    }

    const int button;

    EVENT_TYPE(MOUSE_BUTTON_PRESSED)
};

struct mouse_button_release_event : public event
{
    mouse_button_release_event(int button)
        : button(button)
    {
    }

    const int button;

    EVENT_TYPE(MOUSE_BUTTON_RELEASED)
};

struct mouse_move_event : public event
{
    mouse_move_event(double xpos, double ypos)
        : xpos(xpos)
        , ypos(ypos)
    {
    }

    const double xpos;
    const double ypos;

    EVENT_TYPE(MOUSE_BUTTON_MOVED)
};

struct mouse_scroll_event : public event
{
    mouse_scroll_event(double xoffset, double yoffset)
        : xoffset(xoffset)
        , yoffset(yoffset)
    {
    }

    const double xoffset;
    const double yoffset;

    EVENT_TYPE(MOUSE_BUTTON_SCROLLED)
};

class event_dispatcher
{
  public:
    event_dispatcher(event &event)
        : e(event)
    {
    }

    template <typename T, typename F> bool dispatch(const F &&fn)
    {
        if (e.get_type() == T::get_static_type())
        {
            e.b_isHandled |= fn(static_cast<T &>(e));
            return true;
        }
        return false;
    }

    template <typename T, typename F, typename C> bool dispatch(C *instance, const F &fn)
    {
        if (e.get_type() == T::get_static_type())
        {
            e.b_isHandled |= (instance->*fn)(static_cast<T &>(e));
            return true;
        }
        return false;
    }

  private:
    event &e;
};

typedef std::function<void(event &&)> EventCallback;

} // namespace engine