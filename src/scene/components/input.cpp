#include "input.hpp"

#include <cstdio>

using namespace engine;

void InputComponent::add_yaw_input(float value)
{
    m_yaw += value;

    update_control_rotation();
}

void InputComponent::add_pitch_input(float value)
{
    m_pitch += value;

    if (m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
    }

    if (m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
    }

    update_control_rotation();
}

void InputComponent::add_movement_input(const glm::vec3 &direction, float value)
{
    m_position += direction * value;
}

void InputComponent::move_forward(float value)
{
    add_movement_input(m_front, value);
}

void InputComponent::move_backward(float value)
{
    add_movement_input(-m_front, value);
}

void InputComponent::move_right(float value)
{
    add_movement_input(m_right, value);
}

void InputComponent::move_left(float value)
{
    add_movement_input(-m_right, value);
}

void InputComponent::update_control_rotation()
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front   = glm::normalize(m_front);
    m_right   = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
}