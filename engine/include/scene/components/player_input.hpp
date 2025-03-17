#pragma once

#include "core/input.hpp"

#include <unordered_map>

namespace engine
{

enum class PlayerAction
{
    MoveForward,
    MoveBack,

    MoveLeft,
    MoveRight,

    MoveUp,
    MoveDown
};

struct PlayerInput
{
    void bindAction(PlayerAction action, Key key)
    {
        keyBinds[action] = key;
    }

    std::unordered_map<PlayerAction, Key> keyBinds;
};

} // namespace engine