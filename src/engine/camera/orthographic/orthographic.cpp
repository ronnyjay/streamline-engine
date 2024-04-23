#include <engine/camera/orthographic/orthographic.hpp>

extern int window_width;
extern int window_height;

extern engine::window application;

using namespace engine::camera;

orthographic_camera::orthographic_camera()
{
    m_title = "Orthographic Camera";
    update();
}

glm::mat4 const orthographic_camera::projection_matrix() const
{
    float width = (float)application.width() / 200.0f;
    float height = (float)application.height() / 200.0f;
    return glm::ortho(-width, width, -height, height, -1.0f, 1000.0f);
}

glm::mat4 const orthographic_camera::view_matrix() const
{
    return projection_matrix() * m_view_model;
}

void orthographic_camera::update()
{
    m_view_model = (glm::mat4(1.0f));
    m_view_model = (glm::translate(m_view_model, m_position));
    m_view_model = (glm::rotate(m_view_model, glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f)));
    m_view_model = (glm::rotate(m_view_model, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_view_model = (glm::inverse(m_view_model));
}

void orthographic_camera::move(camera::direction direction)
{
    switch (direction)
    {
    case FORWARD:
        if (m_pitch == 0.0f)
        {
            m_position.y += m_movement_speed;
        }
        else
        {
            m_inverted ? m_position.x -= m_movement_speed : m_position.z += m_movement_speed;
        }
        break;
    case BACKWARD:
        if (m_pitch == 0.0f)
        {
            m_position.y -= m_movement_speed;
        }
        else
        {
            m_inverted ? m_position.x += m_movement_speed : m_position.z -= m_movement_speed;
        }
        break;
    case RIGHT:
        m_inverted ? m_position.z += m_movement_speed : m_position.x += m_movement_speed;
        break;
    case LEFT:
        m_inverted ? m_position.z -= m_movement_speed : m_position.x -= m_movement_speed;
        break;
    default:
        break;
    }

    update();
}

void orthographic_camera::move(float xoffset, float yoffset)
{
}

void orthographic_camera::move(float yoffset)
{
}

void orthographic_camera::invert_controls(bool inverted)
{
    m_inverted = inverted;
}
