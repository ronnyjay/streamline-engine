#include "subsystems/input_manager.hpp"

#include "core/logger.hpp"

using namespace engine;

void InputManager::onEvent(event &e)
{
    EventDispatcher dispatcher(e);

    if (captureKeyInput)
    {
        dispatcher.dispatch<key_press_event>(this, &InputManager::onKeyPress);
        dispatcher.dispatch<key_release_event>(this, &InputManager::onKeyRelease);
    }

    if (b_captureMouseInput)
    {
        dispatcher.dispatch<mouse_move_event>(this, &InputManager::onMouseMove);
        dispatcher.dispatch<mouse_scroll_event>(this, &InputManager::onMouseScroll);

        dispatcher.dispatch<mouse_button_press_event>(this, &InputManager::onMouseButtonPress);
        dispatcher.dispatch<mouse_button_release_event>(this, &InputManager::onMouseButtonRelease);
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

inline bool InputManager::onKeyPress(key_press_event &e)
{
    m_keyStates[Key(e.key)] = action::Press;
    return true;
}

inline bool InputManager::onKeyRelease(key_release_event &e)
{
    m_keyStates[Key(e.key)] = action::Release;
    return true;
}

inline bool InputManager::onMouseButtonPress(mouse_button_press_event &e)
{
    m_mouseButtonStates[MouseButton(e.button)] = action::Press;
    return true;
}

inline bool InputManager::onMouseButtonRelease(mouse_button_release_event &e)
{
    m_mouseButtonStates[MouseButton(e.button)] = action::Release;
    return true;
}

inline bool InputManager::onMouseMove(mouse_move_event &e)
{
    std::get<0>(m_mousePositionOffset) = e.xpos;
    std::get<1>(m_mousePositionOffset) = e.ypos;
    return true;
}

inline bool InputManager::onMouseScroll(mouse_scroll_event &e)
{
    std::get<0>(m_mouseScrollOffset) = e.xoffset;
    std::get<1>(m_mouseScrollOffset) = e.yoffset;
    return true;
}