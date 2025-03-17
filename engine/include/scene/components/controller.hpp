#pragma once

namespace engine
{

// clang-format off

enum class MovementMode
{
    Directional, Fixed
};

struct PlayerController
{
    MovementMode movementMode        =  MovementMode::Directional;

    float        yawInput            = 0.0f;
    float        pitchInput          = 0.0f;

    bool         b_moveForward       = false;
    bool         b_moveBack          = false;
    bool         b_moveLeft          = false;
    bool         b_moveRight         = false;
    bool         b_moveUp            = false;
    bool         b_moveDown          = false;

    bool         b_ignoreYawInput    = false;
    bool         b_ignorePitchInput  = false;
};

struct CameraController
{
    MovementMode movementMode       = MovementMode::Directional;

    float        yawInput           = 0.0f;
    float        pitchInput         = 0.0f;

    bool         b_followEntity     = true;

    bool         b_moveForward      = false;
    bool         b_moveBack         = false;
    bool         b_moveLeft         = false;
    bool         b_moveRight        = false;
    bool         b_moveUp           = false;
    bool         b_moveDown         = false;

    bool         b_ignoreYawInput   = false;
    bool         b_ignorePitchInput = false;
};

// clang-format on

} // namespace engine
