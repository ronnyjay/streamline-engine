#include <engine/camera/orthographic/orthographic.hpp>

#include <engine/application/application.hpp>
#include <engine/camera/orthographic/orthographic.hpp>

using namespace engine;

extern Application application;

void OrthographicCamera::update_vectors()
{
    m_view_model = glm::mat4(1.0f);
    m_view_model = glm::translate(m_view_model, position());
    m_view_model = glm::rotate(m_view_model, glm::radians(yaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    m_view_model = glm::rotate(m_view_model, glm::radians(pitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    m_view_model = glm::inverse(m_view_model);
}

glm::mat4 const OrthographicCamera::projection_matrix() const
{
    auto width = static_cast<float>(application.window()->width());
    auto height = static_cast<float>(application.window()->height());
    auto aspect_ratio = width / height;
    return glm::ortho(-2.0f * aspect_ratio * zoom(), 2.0f * aspect_ratio * zoom(), -2.0f * zoom(), 2.0f * zoom(), -1.0f, 1000.0f);
}

glm::mat4 const OrthographicCamera::view_matrix() const
{
    return projection_matrix() * m_view_model;
}

void OrthographicCamera::move(CameraDirection direction)
{
    switch (direction)
    {
    case Forward:
        set_position(glm::vec3(position().x, position().y, position().z + movement_speed()));
        break;
    case Backward:
        set_position(glm::vec3(position().x, position().y, position().z - movement_speed()));
        break;
    case Left:
        set_position(glm::vec3(position().x - movement_speed(), position().y, position().z));
        break;
    case Right:
        set_position(glm::vec3(position().x + movement_speed(), position().y, position().z));
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

void OrthographicCamera::move(double x_pos, double y_pos)
{
}

void OrthographicCamera::move(double y_offset)
{
}
