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

    void   onEvent(Event &e);

    double getMousePosOffsetX() noexcept;
    double getMousePosOffsetY() noexcept;

    bool   isKeyPressed(Key key) const noexcept;
    bool   isMouseButtonPressed(MouseButton btn) const noexcept;

  private:
    bool onKeyPress(KeyPressEvent &e);
    bool onKeyRelease(KeyReleaseEvent &e);

    bool onMouseButtonPress(MouseButtonPressEvent &e);
    bool onMouseButtonRelease(MouseButtonReleaseEvent &e);

    bool onMouseMove(MouseMoveEvent &e);
    bool onMouseScroll(MouseScrollEvent &e);

  private:
    std::tuple<double, double>              m_mouseScrollOffset;
    std::tuple<double, double>              m_mousePositionOffset;

    std::unordered_map<Key, action>         m_keyStates;
    std::unordered_map<MouseButton, action> m_mouseButtonStates;
};

} // namespace engine