#include "camera.hpp"

using namespace engine;

void CameraComponent::set_projection(Projection proj)
{
    if (m_projection_type != proj)
    {
        m_projection_type = proj;
        update_projection_matrix();
    }
}

void CameraComponent::set_near(float near)
{
    if (m_near != near)
    {
        m_near = near;
        update_projection_matrix();
    }
}

void CameraComponent::set_far(float far)
{
    if (m_far != far)
    {
        m_far = far;
        update_projection_matrix();
    }
}

void CameraComponent::set_fov(float fov)
{
    if (m_fov != fov)
    {
        m_fov = fov;
        update_projection_matrix();
    }
}

void CameraComponent::set_yaw(float yaw)
{
    if (m_yaw != yaw)
    {
        m_yaw = yaw;
        update_view_matrix();
    }
}

void CameraComponent::set_pitch(float pitch)
{
    if (m_pitch != pitch)
    {
        m_pitch = pitch;
        update_view_matrix();
    }
}

void CameraComponent::set_position(const glm::vec3 &position)
{
    if (m_position != position)
    {
        m_position = position;
        update_view_matrix();
    }
}

void CameraComponent::set_aspect_ratio(uint16_t width, uint16_t height)
{
    if (width != 0 && height != 0)
    {
        m_ratio = (float)width / (float)height;
        update_projection_matrix();
    }
}

void CameraComponent::update_projection_matrix()
{
    if (m_projection_type == Projection::PERSPECTIVE)
    {
        m_projection_matrix = glm::perspective(glm::radians(m_fov), m_ratio, m_near, m_far);
    }
    else
    {
        float x             = 2.0f * m_ratio * m_fov;
        float y             = 2.0f * m_fov;

        m_projection_matrix = glm::ortho(-x, x, -y, y, m_near, m_far);
    }
}

void CameraComponent::update_view_matrix()
{
    if (m_projection_type == Projection::PERSPECTIVE)
    {
        m_front.x     = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y     = sin(glm::radians(m_pitch));
        m_front.z     = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_right       = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_up          = glm::normalize(glm::cross(m_right, m_front));

        m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
    }
    else
    {
        m_view_matrix = glm::translate(glm::mat4(1.0f), m_position);
        m_view_matrix = glm::rotate(m_view_matrix, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        m_view_matrix = glm::rotate(m_view_matrix, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        m_view_matrix = glm::inverse(m_view_matrix);
    }
}