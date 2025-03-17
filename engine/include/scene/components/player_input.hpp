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
    PlayerInput()
    {
        // clang-format off
        bindAction(PlayerAction::MoveForward, Key::W);
        bindAction(PlayerAction::MoveBack   , Key::S);
        bindAction(PlayerAction::MoveRight  , Key::D);
        bindAction(PlayerAction::MoveLeft   , Key::A);
        bindAction(PlayerAction::MoveUp     , Key::Space);
        bindAction(PlayerAction::MoveDown   , Key::LeftShift);
        // clang-format on
    }

    void bindAction(PlayerAction action, Key key)
    {
        keyBinds[action] = key;
    }

    std::unordered_map<PlayerAction, Key> keyBinds;
};

} // namespace engine