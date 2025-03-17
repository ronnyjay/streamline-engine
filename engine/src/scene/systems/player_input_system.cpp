#include "scene/systems/player_input_system.hpp"
#include "scene/scene.hpp"

#include "subsystems/input_manager.hpp"

using namespace engine;

void PlayerInputSystem::update(double dt)
{
    updatePlayerControllers(dt);
    updateCameraControllers(dt);
}

void PlayerInputSystem::updatePlayerControllers(double dt)
{
    auto view = m_scene->m_registry.view<PlayerInput, PlayerController>();

    for (const auto &entity : view)
    {
        auto [input, controller] = view.get(entity);

        for (const auto &bind : input.keyBinds)
        {
            if (InputManager::getInstance().isKeyPressed(bind.second))
            {
                // clang-format off
                switch (bind.first)
                {
                case PlayerAction::MoveForward:
                    controller.b_moveForward = true;
                    break;
                case PlayerAction::MoveBack:
                    controller.b_moveBack    = true;
                    break;
                case PlayerAction::MoveRight:
                    controller.b_moveRight   = true;
                    break;
                case PlayerAction::MoveLeft:
                    controller.b_moveLeft    = true;
                    break;
                case PlayerAction::MoveUp:
                    controller.b_moveUp      = true;
                    break;
                case PlayerAction::MoveDown:
                    controller.b_moveDown    = true;
                    break;
                }
                // clang-format on
            }
        }

        // clang-format off
        controller.yawInput   += InputManager::getInstance().getMouseOffsetX();
        controller.pitchInput += InputManager::getInstance().getMouseOffsetY();
        // clang-format on
    }
}

void PlayerInputSystem::updateCameraControllers(double dt)
{
    auto view = m_scene->m_registry.view<PlayerInput, CameraController>();

    for (const auto &entity : view)
    {
        auto [input, controller] = view.get(entity);

        for (const auto &bind : input.keyBinds)
        {
            if (InputManager::getInstance().isKeyPressed(bind.second))
            {
                // clang-format off
                switch (bind.first)
                {
                case PlayerAction::MoveForward:
                    controller.b_moveForward = true;
                    break;
                case PlayerAction::MoveBack:
                    controller.b_moveBack    = true;
                    break;
                case PlayerAction::MoveRight:
                    controller.b_moveRight   = true;
                    break;
                case PlayerAction::MoveLeft:
                    controller.b_moveLeft    = true;
                    break;
                case PlayerAction::MoveUp:
                    controller.b_moveUp      = true;
                    break;
                case PlayerAction::MoveDown:
                    controller.b_moveDown    = true;
                    break;
                }
                // clang-format on
            }
        }

        // clang-format off
        controller.yawInput   += InputManager::getInstance().getMouseOffsetX();
        controller.pitchInput += InputManager::getInstance().getMouseOffsetY();
        // clang-format on
    }
}
