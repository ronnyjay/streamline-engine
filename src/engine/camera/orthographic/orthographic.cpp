#include <engine/camera/orthographic/orthographic.hpp>

extern int window_width;
extern int window_height;

using namespace engine::camera;

orthographic_camera::orthographic_camera()
{
    m_pitch = 36.0f;
    m_movement_speed = 0.5f;

    update();
}

glm::mat4 const orthographic_camera::projection_matrix() const
{
    auto width = 16.0f;
    auto height = 9.0f;

    return glm::ortho((float)(-width), (float)width, (float)(-height), (float)(height), -1.0f, 1000.0f);
}

glm::mat4 const orthographic_camera::view_matrix() const
{
    return projection_matrix() * m_view_model;
}

void orthographic_camera::update()
{
    m_view_model = (glm::mat4(1.0f));
    m_view_model = (glm::translate(m_view_model, m_position));
    m_view_model = (glm::rotate(m_view_model, glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_view_model = (glm::inverse(m_view_model));
}

void orthographic_camera::move(camera::direction direction)
{
    switch (direction)
    {
    case FORWARD:
        m_position.z += m_movement_speed;
        break;
    case BACKWARD:
        m_position.z -= m_movement_speed;
        break;
    case RIGHT:
        m_position.x += m_movement_speed;
        break;
    case LEFT:
        m_position.x -= m_movement_speed;
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
