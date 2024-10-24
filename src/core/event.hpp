#pragma once

#include <functional>
#include <sstream>
#include <string>

namespace engine
{

typedef enum
{
    None,
    WindowResized,
    KeyPressed,
    MousePressed,
    MouseMoved,
    MouseScrolled
} EventType;

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType get_static_type()                                                                                 \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType get_event_type() const override                                                                  \
    {                                                                                                                  \
        return get_static_type();                                                                                      \
    }

struct Event
{

    /**
     * @brief
     *
     */
    virtual ~Event() = default;

    static EventType get_static_type()
    {
        return EventType::None;
    }

    /**
     * @brief
     *
     * @return EventType
     */
    virtual EventType get_event_type() const = 0;

    /**
     * @brief
     *
     * @return std::string
     */
    virtual std::string to_string() const
    {
        return "None";
    }
};

struct WindowResizeEvent : public Event
{
    /**
     * @brief Construct a new Window Resized Event object
     *
     * @param width
     * @param height
     */
    WindowResizeEvent(int width, int height)
        : width(width)
        , height(height)
    {
    }

    /**
     * @brief
     *
     */
    int width;

    /**
     * @brief
     *
     */
    int height;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string to_string() const override
    {
        return (std::stringstream() << "WindowResizedEvent - Width: " << width << ", Height: " << height).str();
    }

    EVENT_CLASS_TYPE(WindowResized)
};

struct KeyPressEvent : public Event
{
    /**
     * @brief Construct a new Key Pressed Event object
     *
     * @param key
     * @param scancode
     * @param action
     * @param mods
     */
    KeyPressEvent(int key, int scancode, int action, int mods)
        : key(key)
        , scancode(scancode)
        , action(action)
        , mods(mods)
    {
    }

    /**
     * @brief
     *
     */
    int key;

    /**
     * @brief
     *
     */
    int scancode;

    /**
     * @brief
     *
     */
    int action;

    /**
     * @brief
     *
     */
    int mods;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string to_string() const override
    {
        return (std::stringstream() << "KeyPressedEvent - Key: " << key << ", Action: " << action << ", Mods: " << mods)
            .str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

struct MousePressEvent : public Event
{
    /**
     * @brief Construct a new Mouse Pressed Event object
     *
     * @param button
     * @param action
     * @param mods
     */
    MousePressEvent(int button, int action, int mods)
        : button(button)
        , action(action)
        , mods(mods)
    {
    }

    /**
     * @brief
     *
     */
    int button;

    /**
     * @brief
     *
     */
    int action;

    /**
     * @brief
     *
     */
    int mods;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string to_string() const override
    {
        return (std::stringstream() << "MousePressedEvent - Button: " << button << ", Action: " << action
                                    << ", Mods: " << mods)
            .str();
    }

    EVENT_CLASS_TYPE(MousePressed)
};

struct MouseMoveEvent : public Event
{
    /**
     * @brief Construct a new Mouse Moved Event object
     *
     * @param xpos
     * @param ypos
     */
    MouseMoveEvent(double xpos, double ypos)
        : x_pos(xpos)
        , y_pos(ypos)
    {
    }

    /**
     * @brief
     *
     */
    double x_pos;

    /**
     * @brief
     *
     */
    double y_pos;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string to_string() const override
    {
        return (std::stringstream() << "MouseMovedEvent - xPos: " << x_pos << ", yPos: " << y_pos).str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
};

struct MouseScrollEvent : public Event
{
    /**
     * @brief Construct a new Mouse Scrolled Event object
     *
     * @param xoffset
     * @param yoffset
     */
    MouseScrollEvent(double xoffset, double yoffset)
        : x_offset(xoffset)
        , y_offset(yoffset)
    {
    }

    /**
     * @brief
     *
     */
    double x_offset;

    /**
     * @brief
     *
     */
    double y_offset;

    /**
     * @brief
     *
     * @return std::string
     */
    std::string to_string() const override
    {
        return (std::stringstream() << "MouseScrolledEvent - xOffset: " << x_offset << ", yOffset: " << y_offset).str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
};

class EventDispatcher
{
  public:
    ~EventDispatcher() = default;

    template <typename T> void on(std::function<void(T &)> fn)
    {
        m_events[T::get_static_type()] = [fn](Event &e)
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
    std::unordered_map<EventType, std::function<void(Event &)>> m_events;
};

} // namespace engine