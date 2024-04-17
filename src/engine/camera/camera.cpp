#include <engine/camera/camera.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace engine;

extern int window_width;
extern int window_height;

camera::camera()
{
    m_position = glm::vec3(0, 1, 0);
    m_direction = glm::vec3(0, 0, 1);
    m_up = glm::vec3(0, 1, 0);
}

camera::camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
    : m_position(position), m_direction(direction), m_up(up)
{
}

glm::mat4 const camera::projection() const
{
    return glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 1000.0f);
}

glm::mat4 const camera::view() const
{
    return glm::lookAt(m_position, m_position + m_direction, m_up);
}
