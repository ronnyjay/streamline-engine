#pragma once

#include "core/event.hpp"
#include "core/input.hpp"
#include "core/singleton.hpp"

namespace engine
{

struct InputManager : public Singleton<InputManager>
{
    void onKeyPress(key_press_event &e)
    {
    }

    void onMouseButonPress(mouse_button_press_event &e)
    {
    }

    bool onMouseMove(mouse_move_event &e)
    {
        std::get<0>(MousePosition) = e.xpos;
        std::get<1>(MousePosition) = e.ypos;
        return true;
    }

    bool isKeyPressed(Key key) const noexcept
    {
        if (KeyStates.find(key) != KeyStates.end())
        {
            if (KeyStates.at(key) == action::Press)
            {
                return true;
            }
        }
        return false;
    }

    bool isMouseButtonPressed(mouse_button btn) const noexcept
    {
        if (MouseButtonStates.find(btn) != MouseButtonStates.end())
        {
            if (MouseButtonStates.at(btn) == action::Press)
            {
                return true;
            }
        }
        return false;
    }

    const auto &getMouseOffsetX() const noexcept
    {
        return std::get<0>(MousePosition);
    }

    const auto &getMouseOffsetY() const noexcept
    {
        return std::get<1>(MousePosition);
    }

  private:
    std::unordered_map<Key, action>          KeyStates;
    std::tuple<double, double>               MouseScroll;
    std::tuple<double, double>               MousePosition;
    std::unordered_map<mouse_button, action> MouseButtonStates;
};

} // namespace engine