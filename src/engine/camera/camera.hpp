#pragma once

#include <GLFW/glfw3.h>

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
    up,
    down,
    forward,
    backward,
    left,
    right
} movement_direction;

typedef enum
{
    x,
    y,
    z
} rotation_axis;

class camera_t
{
  public:
    camera_t() : m_view_matrix(1.0f), m_speed(0.05f), m_sensitivity(0.1f), m_zoom(45.0f)
    {
    }

    virtual glm::mat4 const projection_matrix() const = 0;
    virtual glm::mat4 const view_projection_matrix() const = 0;

    virtual void update() = 0;
    virtual void move(movement_direction) = 0;          // keyboard movement
    virtual void move(float offset, float yoffset) = 0; // mouse movement
    virtual void move(float yoffset) = 0;               // mouse scroll

    glm::mat4 const &view_matrix() const
    {
        return m_view_matrix;
    }

    void set_view_matrix(const glm::mat4 &view_matrix)
    {
        m_view_matrix = view_matrix;
    }

    const glm::vec3 &position() const
    {
        return m_position;
    }

    void set_position(const glm::vec3 &position)
    {
        m_position = position;

        update();
    }

    float rotation(rotation_axis axis) const
    {
        switch (axis)
        {
        case x:
            return m_rotation_x;
        case y:
            return m_rotation_y;
        case z:
            return m_rotation_z;
        }

        return 0.0f;
    }

    void set_rotation(rotation_axis axis, float rotation)
    {
        switch (axis)
        {
        case x:
            m_rotation_x = rotation;
            break;
        case y:
            m_rotation_y = rotation;
            break;
        case z:
            m_rotation_z = rotation;
            break;
        }

        update();
    }

    float speed() const
    {
        return m_speed;
    }

    void set_speed(float speed)
    {
        m_speed = speed;
    }

    float sensitivity() const
    {
        return m_sensitivity;
    }

    void set_sensitivity(float sensitivity)
    {
        m_sensitivity = sensitivity;
    }

    float zoom() const
    {
        return m_zoom;
    }

    void set_zoom(float zoom)
    {
        m_zoom = zoom;
    }

    ~camera_t() = default;

  protected:
    glm::mat4 m_view_matrix;

  private:
    glm::vec3 m_position;

    float m_rotation_x;
    float m_rotation_y;
    float m_rotation_z;

    float m_speed;
    float m_sensitivity;
    float m_zoom;
};

} // namespace camera

}; // namespace engine