#include <engine/camera/perspective/perspective.hpp>

extern int window_width;
extern int window_height;

using namespace engine::camera;

perspective_camera::perspective_camera()
    : m_direction(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), m_world_up(m_up), m_yaw(90.0f), m_pitch(0.0f)
{
}

glm::mat4 const perspective_camera::projection_matrix() const
{
    return glm::perspective(glm::radians(zoom()), (float)window_width / (float)window_height, 0.1f, 100.0f);
}

glm::mat4 const perspective_camera::view_projection_matrix() const
{
    return glm::lookAt(position(), position() + m_direction, m_up);
}

void perspective_camera::update()
{
    m_view_matrix = (glm::mat4(1.0f));
    m_view_matrix = (glm::translate(view_matrix(), position()));
    m_view_matrix = (glm::rotate(view_matrix(), glm::radians(rotation(rotation_axis::x)), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_view_matrix = (glm::inverse(view_matrix()));

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction = glm::normalize(direction);

    glm::vec3 forward_horizontal;
    forward_horizontal.x = cos(glm::radians(m_yaw));
    forward_horizontal.y = 0;
    forward_horizontal.z = sin(glm::radians(m_yaw));
    m_forward_horizontal = glm::normalize(forward_horizontal);

    m_right = glm::normalize(glm::cross(m_direction, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_direction));
}

void perspective_camera::move(movement_direction direction)
{
    glm::vec3 camera_position = position();
    float camera_speed = speed();

    switch (direction)
    {
    case up:
        set_position(glm::vec3(camera_position.x, position().y + camera_speed, camera_position.z));
        break;
    case down:
        set_position(glm::vec3(camera_position.x, position().y - camera_speed, camera_position.z));
        break;
    case forward:
        set_position(camera_position + m_forward_horizontal * camera_speed);
        break;
    case backward:
        set_position(camera_position - m_forward_horizontal * camera_speed);
        break;
    case right:
        set_position(camera_position + glm::normalize(glm::cross(m_direction, m_up)) * camera_speed);
        break;
    case left:
        set_position(camera_position - glm::normalize(glm::cross(m_direction, m_up)) * camera_speed);
        break;
    }
}

void perspective_camera::move(float xoffset, float yoffset)
{
    float sens = sensitivity();

    xoffset *= sens;
    yoffset *= sens;

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
    float updated_zoom = zoom() - (float)yoffset;

    if (updated_zoom < 1.0f)
    {
        updated_zoom = 1.0f;
    }
    else if (updated_zoom > 45.0f)
    {
        updated_zoom = 45.0f;
    }

    set_zoom(updated_zoom);
}