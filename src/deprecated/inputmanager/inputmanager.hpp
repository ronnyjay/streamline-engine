#pragma once

#include <engine/glfw3.h>

#include <engine/logger/logger.hpp>

#include <memory>
#include <unordered_map>

namespace engine
{

struct KeyEvent
{
    KeyEvent()
        : key(0)
        , scancode(0)
        , action(0)
        , mods(0)
    {
    }

    KeyEvent(const KeyEvent &) = default;

    int key;
    int scancode;
    int action;
    int mods;
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

class InputManager
{
  public:
    static InputManager &Instance();

    inline void RegisterKeyState(int key, int scancode, int action, int mods)
    {
        m_KeyStates[key] = action;
    }

    inline void RegisterCursorEvent(double x_offset, double y_offset)
    {
        m_LastCursorEvent.x_offset = x_offset;
        m_LastCursorEvent.y_offset = y_offset;
    }

    inline void RegisterScrollEvent(double x_offset, double y_offset)
    {
        m_LastScrollEvent.x_offset = x_offset;
        m_LastScrollEvent.y_offset = y_offset;
    }

    inline const KeyStateRegister &KeyStates() const
    {
        return m_KeyStates;
    }

    inline const MouseEvent LastCursorEvent()
    {
        MouseEvent event = m_LastCursorEvent;

        m_LastCursorEvent.x_offset = 0.0;
        m_LastCursorEvent.y_offset = 0.0;

        return event;
    }

    inline const MouseEvent LastScrollEvent()
    {
        MouseEvent event = m_LastScrollEvent;

        m_LastScrollEvent.x_offset = 0.0;
        m_LastScrollEvent.y_offset = 0.0;

        return event;
    }

  private:
    inline InputManager(){};

    MouseEvent m_LastCursorEvent;
    MouseEvent m_LastScrollEvent;

    KeyStateRegister m_KeyStates;

    static std::unique_ptr<InputManager> m_Instance;
};

} // namespace engine