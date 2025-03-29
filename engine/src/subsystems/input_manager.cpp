#include "subsystems/input_manager.hpp"

using namespace engine;

void InputManager::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);

    if (b_captureKeyInput)
    {
        dispatcher.dispatch<KeyPressEvent>(this, &InputManager::onKeyPress);
        dispatcher.dispatch<KeyReleaseEvent>(this, &InputManager::onKeyRelease);
    }

    if (b_captureMouseInput)
    {
        dispatcher.dispatch<MouseMoveEvent>(this, &InputManager::onMouseMove);
        dispatcher.dispatch<MouseScrollEvent>(this, &InputManager::onMouseScroll);

        dispatcher.dispatch<MouseButtonPressEvent>(this, &InputManager::onMouseButtonPress);
        dispatcher.dispatch<MouseButtonReleaseEvent>(this, &InputManager::onMouseButtonRelease);
    }
}

bool InputManager::isKeyPressed(Key key) const noexcept
{
    if (m_keyStates.find(key) != m_keyStates.end())
    {
        if (m_keyStates.at(key) == action::Press)
        {
            return true;
        }
    }
    return false;
}

bool InputManager::isMouseButtonPressed(MouseButton btn) const noexcept
{
    if (m_mouseButtonStates.find(btn) != m_mouseButtonStates.end())
    {
        if (m_mouseButtonStates.at(btn) == action::Press)
        {
            return true;
        }
    }
    return false;
}

double InputManager::getMousePosOffsetX() noexcept
{
    auto offset                        = std::get<0>(m_mousePositionOffset);
    std::get<0>(m_mousePositionOffset) = 0.0;
    return offset;
}

double InputManager::getMousePosOffsetY() noexcept
{
    auto offset                        = std::get<1>(m_mousePositionOffset);
    std::get<1>(m_mousePositionOffset) = 0.0;
    return offset;
}

inline bool InputManager::onKeyPress(KeyPressEvent &e)
{
    m_keyStates[Key(e.key)] = action::Press;
    return true;
}

inline bool InputManager::onKeyRelease(KeyReleaseEvent &e)
{
    m_keyStates[Key(e.key)] = action::Release;
    return true;
}

inline bool InputManager::onMouseButtonPress(MouseButtonPressEvent &e)
{
    m_mouseButtonStates[MouseButton(e.button)] = action::Press;
    return true;
}

inline bool InputManager::onMouseButtonRelease(MouseButtonReleaseEvent &e)
{
    m_mouseButtonStates[MouseButton(e.button)] = action::Release;
    return true;
}

inline bool InputManager::onMouseMove(MouseMoveEvent &e)
{
    std::get<0>(m_mousePositionOffset) = e.xpos;
    std::get<1>(m_mousePositionOffset) = e.ypos;
    return true;
}

inline bool InputManager::onMouseScroll(MouseScrollEvent &e)
{
    std::get<0>(m_mouseScrollOffset) = e.xoffset;
    std::get<1>(m_mouseScrollOffset) = e.yoffset;
    return true;
}