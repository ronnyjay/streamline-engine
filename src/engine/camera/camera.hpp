#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace engine
{

namespace camera
{

typedef enum
{
    UP,
    DOWN,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} direction;

class camera_t
{
  public:
    camera_t()
    {
    }

    virtual void update() = 0;

    virtual glm::mat4 const projection_matrix() const = 0;
    virtual glm::mat4 const view_matrix() const = 0;

    virtual void move(direction) = 0;                    // keyboard input
    virtual void move(float xoffset, float yoffset) = 0; // mouse movement
    virtual void move(float yoffset) = 0;                // mouse scroll

    void set_position(glm::vec3 position)
    {
        m_position = position;
        update();
    }

    void set_yaw(float yaw)
    {
        m_yaw = yaw;
        update();
    }

    void set_pitch(float pitch)
    {
        m_pitch = pitch;
        update();
    }

    void set_zoom(float zoom)
    {
        m_zoom = zoom;
        update();
    }

    void set_movement_speed(float speed)
    {
        m_movement_speed = speed;
        update();
    }

    void set_mouse_sensitivity(float sensitivity)
    {
        m_mouse_sensitivity = sensitivity;
        update();
    }

  public:
    glm::vec3 m_position;

    float m_yaw;
    float m_pitch;

    float m_zoom;

    float m_movement_speed;
    float m_mouse_sensitivity;
};

} // namespace camera

}; // namespace engine