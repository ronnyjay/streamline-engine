#include "engine/camera/camera.hpp"
#include <engine/camera/orthographic/orthographic.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

extern int window_width;
extern int window_height;

using namespace engine::camera;

orthographic_camera::orthographic_camera()
    : m_position(0.0f, 15.0f, 50.0f), m_direction(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), m_speed(0.5f)
{
    m_scale = 50.0f;
}

glm::mat4 const orthographic_camera::projection() const
{
    float width = m_scale * ((float)window_width / (float)window_height) / 2;
    float height = m_scale / 2;

    return glm::ortho(-width, width, -height, height, 0.1f, 100.0f);
}

glm::mat4 const orthographic_camera::view() const
{
    return glm::lookAt(m_position, m_direction, m_up);
}

void orthographic_camera::move(movement_direction direction)
{
    glm::vec3 right_direction = glm::normalize(glm::cross(m_direction, m_up));
    glm::vec3 normalized_direction = glm::normalize(m_direction);

    switch (direction)
    {
    case forward:
        m_position -= m_speed * normalized_direction;
        break;
    case backward:
        m_position += m_speed * normalized_direction;
        break;
    case right:
        m_position -= m_speed * right_direction;
        break;
    case left:
        m_position += m_speed * right_direction;
        break;
    default:
        break;
    }
}