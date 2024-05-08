#pragma once

#include <engine/debug/debug.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

#include <string>

namespace engine
{

// default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 0.1f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 1.0f;

typedef enum
{
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
} CameraDirection;

class Camera : public Debuggable
{
  public:
    Camera(const std::string &identifier, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
        : Debuggable(identifier), m_movement_speed(SPEED), m_mouse_sensitivity(SENSITIVITY)
    {
        m_yaw = yaw;
        m_pitch = pitch;
        m_zoom = zoom;
        m_position = position;
    }

    virtual void update_vectors() = 0;

    virtual glm::mat4 const projection_matrix() const = 0;
    virtual glm::mat4 const view_matrix() const = 0;

    virtual void move(const CameraDirection) = 0; // keyboard input
    virtual void move(const double, double) = 0;  // mouse movement
    virtual void move(const double) = 0;          // mouse scroll

    virtual void draw_debug_info() override;

    const glm::vec3 &position() const;
    void set_position(const glm::vec3 &);

    float yaw() const;
    void set_yaw(const float);

    float pitch() const;
    void set_pitch(const float);

    float zoom() const;
    void set_zoom(const float);

    float movement_speed() const;
    void set_movement_speed(const float);

    float mouse_sensitivity() const;
    void set_mouse_sensitivity(const float);

  private:
    float m_yaw;
    float m_pitch;

    float m_movement_speed;
    float m_mouse_sensitivity;

    float m_zoom;

    glm::vec3 m_position;
};

}; // namespace engine