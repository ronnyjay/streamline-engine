#include <engine/camera/camera.hpp>

using namespace engine;

void Camera::draw_debug_info()
{
    ImGui::DragFloat("Position X", &m_position.x);
    ImGui::DragFloat("Position Y", &m_position.y);
    ImGui::DragFloat("Position Z", &m_position.z);
    ImGui::DragFloat("Yaw", &m_yaw);
    ImGui::DragFloat("Pitch", &m_pitch);
    ImGui::DragFloat("Zoom", &m_zoom);
    ImGui::DragFloat("Speed", &m_movement_speed);
    ImGui::DragFloat("Sensitivity", &m_mouse_sensitivity);

    update_vectors();
}

const glm::vec3 &Camera::position() const
{
    return m_position;
}

void Camera::set_position(const glm::vec3 &position)
{
    m_position = position;
    update_vectors();
}

float Camera::yaw() const
{
    return m_yaw;
}

void Camera::set_yaw(const float yaw)
{
    m_yaw = yaw;
    update_vectors();
}

float Camera::pitch() const
{
    return m_pitch;
}

void Camera::set_pitch(const float pitch)
{
    m_pitch = pitch;
    update_vectors();
}

float Camera::zoom() const
{
    return m_zoom;
}

void Camera::set_zoom(const float zoom)
{
    m_zoom = zoom;
}

float Camera::movement_speed() const
{
    return m_movement_speed;
}

void Camera::set_movement_speed(const float speed)
{
    m_movement_speed = speed;
}

float Camera::mouse_sensitivity() const
{
    return m_mouse_sensitivity;
}

void Camera::set_mouse_sensitivity(const float sensitivity)
{
    m_mouse_sensitivity = sensitivity;
}
