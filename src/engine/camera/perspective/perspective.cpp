#include <engine/camera/perspective/perspective.hpp>

extern int window_width;
extern int window_height;

extern engine::window application;

using namespace engine::camera;

perspective_camera::perspective_camera() : m_front(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), m_world_up(m_up)
{
    m_position = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw = 90.0f;
    m_zoom = 45.0f;
    m_title = "Perspective Camera";

    update();
}

void perspective_camera::update()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    glm::vec3 forward_horizontal;
    forward_horizontal.x = cos(glm::radians(m_yaw));
    forward_horizontal.y = 0;
    forward_horizontal.z = sin(glm::radians(m_yaw));
    m_forward_horizontal = glm::normalize(forward_horizontal);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 const perspective_camera::projection_matrix() const
{
    return glm::perspective(glm::radians(m_zoom), (float)application.width() / (float)application.height(), 0.1f,
                            1000.0f);
}

glm::mat4 const perspective_camera::view_matrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void perspective_camera::move(camera::direction direction)
{
    switch (direction)
    {
    case UP:
        m_position.y += m_movement_speed;
        break;
    case DOWN:
        m_position.y -= m_movement_speed;
        break;
    case FORWARD:
        m_position += m_forward_horizontal * m_movement_speed;
        break;
    case BACKWARD:
        m_position -= m_forward_horizontal * m_movement_speed;
        break;
    case RIGHT:
        m_position += glm::normalize(glm::cross(m_front, m_up)) * m_movement_speed;
        break;
    case LEFT:
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_movement_speed;
        break;
    }
}

void perspective_camera::move(float xoffset, float yoffset)
{
    xoffset *= m_mouse_sensitivity;
    yoffset *= m_mouse_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
    }
    if (m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
    }

    update();
}

void perspective_camera::move(float yoffset)
{
    m_zoom -= yoffset;

    if (m_zoom < 1.0f)
    {
        m_zoom = 1.0f;
    }

    if (m_zoom > 45.0f)
    {
        m_zoom = 45.0f;
    }
}
