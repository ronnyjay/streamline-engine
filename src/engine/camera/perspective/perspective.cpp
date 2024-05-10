#include <engine/application/application.hpp>
#include <engine/camera/perspective/perspective.hpp>

using namespace engine;

extern Application application;

void PerspectiveCamera::update_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw())) * cos(glm::radians(pitch()));
    front.y = sin(glm::radians(pitch()));
    front.z = sin(glm::radians(yaw())) * cos(glm::radians(pitch()));
    m_front = glm::normalize(front);

    glm::vec3 forward_horizontal;
    forward_horizontal.x = cos(glm::radians(yaw()));
    forward_horizontal.y = 0;
    forward_horizontal.z = sin(glm::radians(yaw()));
    m_forward_horizontal = glm::normalize(forward_horizontal);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 const PerspectiveCamera::projection_matrix() const
{
    auto width = static_cast<float>(application.window()->width());
    auto height = static_cast<float>(application.window()->height());
    return glm::perspective(glm::radians(zoom()), width / height, 0.1f, 1000.0f);
}

glm::mat4 const PerspectiveCamera::view_matrix() const
{
    return glm::lookAt(position(), position() + m_front, m_up);
}

void PerspectiveCamera::move(CameraDirection directon)
{
    switch (directon)
    {
    case Forward:
        if (m_lock_horizontal_movement)
        {
            set_position(position() + (m_forward_horizontal * movement_speed()));
        }
        else
        {
            set_position(position() + (m_front * movement_speed()));
        }
        break;
    case Backward:
        if (m_lock_horizontal_movement)
        {
            set_position(position() - (m_forward_horizontal * movement_speed()));
        }
        else
        {
            set_position(position() - (m_front * movement_speed()));
        }
        break;
    case Left:
        set_position(position() - (glm::normalize(glm::cross(m_front, m_up)) * movement_speed()));
        break;
    case Right:
        set_position(position() + (glm::normalize(glm::cross(m_front, m_up)) * movement_speed()));
        break;
    case Up:
        set_position(glm::vec3(position().x, position().y + movement_speed(), position().z));
        break;
    case Down:
        set_position(glm::vec3(position().x, position().y - movement_speed(), position().z));
        break;
    }

    update_vectors();
}

void PerspectiveCamera::move(double x_pos, double y_pos)
{
    x_pos *= mouse_sensitivity();
    y_pos *= mouse_sensitivity();

    set_yaw(yaw() + x_pos);
    set_pitch(pitch() + y_pos);

    if (pitch() > 89.0f)
    {
        set_pitch(89.0f);
    }
    if (pitch() < -89.0f)
    {
        set_pitch(-89.0f);
    }

    update_vectors();
}

void PerspectiveCamera::move(double y_offset)
{
    set_zoom(zoom() - y_offset);

    if (zoom() < 1.0f)
    {
        set_zoom(1.0f);
    }

    if (zoom() > 45.0f)
    {
        set_zoom(45.0f);
    }
}

void PerspectiveCamera::draw_debug_info()
{
    Camera::draw_debug_info();

    ImGui::Text("Lock Horizontal Movement");
    ImGui::SameLine();
    ImGui::Checkbox("##lock_horizontal_movement", &m_lock_horizontal_movement);
}

void PerspectiveCamera::lock_horizontal_movement(bool lock)
{
    m_lock_horizontal_movement = lock;
}