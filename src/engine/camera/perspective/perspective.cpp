#include <engine/camera/perspective/perspective.hpp>

extern int window_width;
extern int window_height;

using namespace engine::camera;

perspective_camera::perspective_camera()
    : m_position(0.0f, 1.0f, 0.0f), m_direction(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), m_speed(0.05f)
{
}

glm::mat4 const perspective_camera::projection() const
{
    return glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
}

glm::mat4 const perspective_camera::view() const
{
    return glm::lookAt(m_position, m_position + m_direction, m_up);
}

void perspective_camera::move(movement_direction direction)
{
    switch (direction)
    {
    case forward:
        m_position = m_position + (m_speed * 2 * m_direction);
        break;
    case backward:
        m_position = m_position - (m_speed * 2 * m_direction);
        break;
    case right:
        m_position = m_position + glm::normalize(glm::cross(m_direction, m_up)) * m_speed;
        break;
    case left:
        m_position = m_position - glm::normalize(glm::cross(m_direction, m_up)) * m_speed;
        break;
    }
}