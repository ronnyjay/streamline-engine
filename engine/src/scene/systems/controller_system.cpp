#include "scene/systems/controller_system.hpp"
#include "scene/scene.hpp"

using namespace engine;

void ControllerSystem::update(double dt)
{
    updatePlayerPositions(dt);
    updatePlayerRotations(dt);
}

void ControllerSystem::updatePlayerPositions(double dt)
{
    auto view = m_scene->m_registry.view<PlayerController, PlayerMove, Transform>();

    for (const auto &entity : view)
    {
        auto [controller, move, transform] = view.get(entity);

        if (controller.b_moveForward)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation += transform.getFront() * move.speed * static_cast<float>(dt);
            }
            if (controller.movementMode == MovementMode::Fixed)
            {
                transform.translation.z += move.speed * static_cast<float>(dt);
            }
            controller.b_moveForward = false;
        }
        if (controller.b_moveBack)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation -= transform.getFront() * move.speed * static_cast<float>(dt);
            }
            if (controller.movementMode == MovementMode::Fixed)
            {
                transform.translation.z -= move.speed * static_cast<float>(dt);
            }
            controller.b_moveBack = false;
        }
        if (controller.b_moveRight)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation += transform.getRight() * move.speed * static_cast<float>(dt);
            }
            if (controller.movementMode == MovementMode::Fixed)
            {
                transform.translation.x += move.speed * static_cast<float>(dt);
            }
            controller.b_moveRight = false;
        }
        if (controller.b_moveLeft)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation -= transform.getRight() * move.speed * static_cast<float>(dt);
            }
            if (controller.movementMode == MovementMode::Fixed)
            {
                transform.translation.x -= move.speed * static_cast<float>(dt);
            }
            controller.b_moveLeft = false;
        }
        if (controller.b_moveUp)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation.y += move.speed * static_cast<float>(dt);
            }
            controller.b_moveUp = false;
        }
        if (controller.b_moveDown)
        {
            if (controller.movementMode == MovementMode::Directional)
            {
                transform.translation.y -= move.speed * static_cast<float>(dt);
            }
            controller.b_moveDown = false;
        }
    }
}

void ControllerSystem::updatePlayerRotations(double dt)
{
    auto view = m_scene->m_registry.view<PlayerController, PlayerLook, Transform>();

    for (const auto &entity : view)
    {
        auto [controller, look, transform] = view.get(entity);

        if (transform.rotation.x > 89.0f)
            transform.rotation.x = 89.0f;

        if (transform.rotation.x < -89.0f)
            transform.rotation.x = -89.0f;

        if (!controller.b_ignoreYawInput)
        {
            transform.rotation.y += controller.yawInput * look.sensitivity;
        }

        if (!controller.b_ignorePitchInput)
        {
            transform.rotation.x += controller.pitchInput * look.sensitivity;
        }

        controller.yawInput = 0.0f;
        controller.pitchInput = 0.0f;
    }
}
