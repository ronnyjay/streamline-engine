#pragma once

#include <GLFW/glfw3.h>

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

    KeyEvent(KeyEvent &) = default;
    KeyEvent(KeyEvent &&) = default;

    int key;
    int scancode;
    int action;
    int mods;
};

// key (GLFW_KEY_...), state (PRESS, RELEASE, REPEAT)
typedef std::unordered_map<int, int> KeyStateRegister;

class InputManager
{
  public:
    static InputManager &Instance();

    inline void RegisterKeyState(int key, int scancode, int action, int mods)
    {
        m_key_states[key] = action;
    }

    inline KeyStateRegister &KeyStates()
    {
        return m_key_states;
    }

  private:
    inline InputManager(){};

    KeyStateRegister m_key_states;

    static std::unique_ptr<InputManager> m_instance;
};

} // namespace engine