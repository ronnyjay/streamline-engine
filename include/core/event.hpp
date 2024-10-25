#pragma once

#include <functional>
#include <map>

namespace engine
{

enum class EventType
{
    None,
    WindowResize
};

#define EVENT_TYPE(type)                                                                                               \
    static EventType GetStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType GetEventType() const override                                                                    \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }

/**
 * @brief
 *
 */
struct Event
{
    /**
     * @brief
     *
     */
    virtual ~Event()
    {
    }

    /**
     * @brief
     *
     * @return EventType
     */
    static EventType GetStaticType()
    {
        return EventType::None;
    }

    /**
     * @brief
     *
     * @return EventType
     */
    virtual EventType GetEventType() const = 0;
};

/**
 * @brief
 *
 */
class EventDispatcher
{
  public:
    /**
     * @brief
     *
     */
    ~EventDispatcher() = default;

    /**
     * @brief
     *
     * @tparam T
     * @param fn
     */
    template <typename T> void on(std::function<void(T &)> fn)
    {
        events[T::GetStaticType()] = [fn](Event &e) { fn(static_cast<T &>(e)); };
    }

  protected:
    /**
     * @brief
     *
     * @param type
     * @param e
     */
    void dispatch(EventType type, Event &&e)
    {
        auto it = events.find(type);

        if (it != events.end())
        {
            it->second(e);
        }
    }

  private:
    std::map<EventType, std::function<void(Event &)>> events;
};

} // namespace engine