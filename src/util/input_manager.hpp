#pragma once

#include <GLFW/glfw3.h>

#include <memory>
#include <unordered_map>

// TODO: Move to core
namespace engine
{

// TODO: Replace KeyEvent, MouseEvent with events from core
struct KeyPressEvent
{
    KeyPressEvent()
        : key(0)
        , scancode(0)
        , action(0)
        , Mods(0)
    {
    }

    KeyPressEvent(const KeyPressEvent &) = default;

    int key;
    int scancode;
    int action;
    int Mods;
};

struct MouseEvent
{
    MouseEvent()
        : x_offset(0.0)
        , y_offset(0.0)
    {
    }

    MouseEvent(const MouseEvent &) = default;

    double x_offset;
    double y_offset;
};

// key (GLFW_KEY_...), state (PRESS, RELEASE, REPEAT)
typedef std::unordered_map<int, int> KeyStateRegister;

// TODO: Change to ResourceManager singleton type
class InputManager
{
  public:
    /**
     * @brief
     *
     * @return InputManager&
     */
    static InputManager &instance();

    /**
     * @brief
     *
     * @param key
     * @param scancode
     * @param action
     * @param mods
     */
    inline void register_key_state(int key, int scancode, int action, int mods)
    {
        if (m_key_states.contains(key))
        {
            if (m_key_states.at(key) == action)
            {
                return;
            }
        }

        m_key_states[key] = action;
    }

    /**
     * @brief
     *
     * @param x_offset
     * @param y_offset
     */
    inline void register_cursor_event(double x_offset, double y_offset)
    {
        m_last_cursor_event.x_offset = x_offset;
        m_last_cursor_event.y_offset = y_offset;
    }

    /**
     * @brief
     *
     * @param x_offset
     * @param y_offset
     */
    inline void register_scroll_event(double x_offset, double y_offset)
    {
        m_last_scroll_event.x_offset = x_offset;
        m_last_scroll_event.y_offset = y_offset;
    }

    /**
     * @brief
     *
     * @return const KeyStateRegister&
     */
    inline const KeyStateRegister &key_states() const
    {
        return m_key_states;
    }

    /**
     * @brief
     *
     * @return const MouseEvent
     */
    inline const MouseEvent last_cursor_event()
    {
        MouseEvent event = m_last_cursor_event;

        m_last_cursor_event.x_offset = 0.0;
        m_last_cursor_event.y_offset = 0.0;

        return event;
    }

    /**
     * @brief
     *
     * @return const MouseEvent
     */
    inline const MouseEvent last_scroll_event()
    {
        MouseEvent event = m_last_scroll_event;

        m_last_scroll_event.x_offset = 0.0;
        m_last_scroll_event.y_offset = 0.0;

        return event;
    }

    /**
     * @brief
     *
     * @return const float
     */
    inline const float cursor_offset_x()
    {
        float offset                 = m_last_cursor_event.x_offset;
        m_last_cursor_event.x_offset = 0.0f;

        return offset;
    }

    /**
     * @brief
     *
     * @return const float
     */
    inline const float cursor_offset_y()
    {
        float offset                 = m_last_cursor_event.y_offset;
        m_last_cursor_event.y_offset = 0.0f;

        return offset;
    }

  private:
    inline InputManager() {};

    KeyStateRegister                     m_key_states;

    MouseEvent                           m_last_cursor_event;
    MouseEvent                           m_last_scroll_event;

    static std::unique_ptr<InputManager> m_instance;
};

} // namespace engine