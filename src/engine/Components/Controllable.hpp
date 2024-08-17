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

    float move_speed = 10.0f;

    float jump_height = 50.0f;
    float jump_cooldown = 0.02224f;
    float time_since_last_jump = 0.0f;

    bool can_jump = true;

    std::unordered_map<int, Action> keybinds;

  private:
};

} // namespace engine