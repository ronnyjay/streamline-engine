#include <engine/camera/orthographic/orthographic.hpp>

extern int window_width;
extern int window_height;

using namespace engine::camera;

orthographic_camera::orthographic_camera()
{
}

void orthographic_camera::update()
{
    m_view_matrix = (glm::mat4(1.0f));
    m_view_matrix = (glm::translate(view_matrix(), position()));
    m_view_matrix = (glm::rotate(view_matrix(), glm::radians(rotation(rotation_axis::x)), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_view_matrix = (glm::inverse(view_matrix()));
}

glm::mat4 const orthographic_camera::projection_matrix() const
{

    auto width = (float)16;
    auto height = (float)9;

    return glm::ortho((float)(-width), (float)width, (float)(-height), (float)(height), -1.0f, 1000.0f);
}

glm::mat4 const orthographic_camera::view_projection_matrix() const
{
    return projection_matrix() * view_matrix();
}

void orthographic_camera::move(movement_direction direction)
{
    switch (direction)
    {
    case forward:
        set_position(glm::vec3(position().x, position().y, position().z + speed()));
        break;
    case backward:
        set_position(glm::vec3(position().x, position().y, position().z - speed()));
        break;
    case right:
        set_position(glm::vec3(position().x + speed(), position().y, position().z));
        break;
    case left:
        set_position(glm::vec3(position().x - speed(), position().y, position().z));
        break;
    default:
        break;
    }
}

void orthographic_camera::move(float xoffset, float yoffset)
{
}

void orthographic_camera::move(float yoffset)
{
}