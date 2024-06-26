#include <engine/Camera/Camera.hpp>

using namespace engine;

float Camera::GetYaw() const
{
    return m_Yaw;
}

void Camera::SetYaw(const float yaw)
{
    m_Yaw = yaw;
    Update();
}

float Camera::GetPitch() const
{
    return m_Pitch;
}

void Camera::SetPitch(const float pitch)
{
    m_Pitch = pitch;
    Update();
}

float Camera::GetZoom() const
{
    return m_Zoom;
}

void Camera::SetZoom(const float zoom)
{
    m_Zoom = zoom;
    Update();
}

float Camera::GetSpeed() const
{
    return m_Speed;
}

void Camera::SetSpeed(const float speed)
{
    m_Speed = speed;
}

float Camera::GetSensitivity() const
{
    return m_Sensitivity;
}

void Camera::SetSensitivity(const float sensitivity)
{
    m_Sensitivity = sensitivity;
}

const glm::vec3 &Camera::GetPosition() const
{
    return m_Position;
}

void Camera::SetPosition(const glm::vec3 &position)
{
    m_Position = position;
    Update();
}

void Camera::DrawDebugInfo()
{
    ImGui::DragFloat("Yaw", &m_Yaw);
    ImGui::DragFloat("Pitch", &m_Pitch);
    ImGui::DragFloat("FOV", &m_Zoom, 1.0f, 1.0f, 120.0f);
    ImGui::DragFloat("Speed", &m_Speed, 1.0f, 10.0f, 100.0f);
    ImGui::DragFloat("Sensitivity", &m_Sensitivity, 0.01f, 0.01, 1.0);
    ImGui::DragFloat("Position X", &m_Position.x);
    ImGui::DragFloat("Position Y", &m_Position.y);
    ImGui::DragFloat("Position Z", &m_Position.z);

    Update();
}
