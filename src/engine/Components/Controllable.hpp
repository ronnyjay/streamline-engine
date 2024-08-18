#pragma once

#include <unordered_map>

namespace engine
{

typedef enum
{
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    Jump
} Action;

typedef std::unordered_map<int, Action> KeyBindMap;

struct Controllable
{
    Controllable() = default;
    Controllable(const Controllable &) = default;

    inline void BindAction(const int key, const Action action)
    {
        keybinds[key] = action;
    }

    float speed = 10.0f;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float sensitivity = 0.005f;

    float jump_height = 5.0f;
    float jump_time = 0.0f;
    float jump_cooldown = 1.0f;

    bool can_jump = true;

    std::unordered_map<int, Action> keybinds;
};

} // namespace engine