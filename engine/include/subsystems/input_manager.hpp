#pragma once

#include "core/event.hpp"
#include "core/input.hpp"
#include "core/singleton.hpp"

namespace engine
{

struct InputManager : public Singleton<InputManager>
{
    bool   captureKeyInput     = true;
    bool   b_captureMouseInput = true;

    void   onEvent(event &e);

    double getMousePosOffsetX() noexcept;
    double getMousePosOffsetY() noexcept;

    bool   isKeyPressed(Key key) const noexcept;
    bool   isMouseButtonPressed(MouseButton btn) const noexcept;

  private:
    bool onKeyPress(key_press_event &e);
    bool onKeyRelease(key_release_event &e);

    bool onMouseButtonPress(mouse_button_press_event &e);
    bool onMouseButtonRelease(mouse_button_release_event &e);

    bool onMouseMove(mouse_move_event &e);
    bool onMouseScroll(mouse_scroll_event &e);

  private:
    std::tuple<double, double>              m_mouseScrollOffset;
    std::tuple<double, double>              m_mousePositionOffset;

    std::unordered_map<Key, action>         m_keyStates;
    std::unordered_map<MouseButton, action> m_mouseButtonStates;
};

} // namespace engine