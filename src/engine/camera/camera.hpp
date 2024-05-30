#pragma once

#include <engine/debug/debuggable.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace engine
{

typedef enum
{
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
} Direction;

// default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 0.1f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 1.0f;

class Camera : public Debuggable
{
  public:
    Camera(glm::vec3 position = glm::vec3(0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
        : m_Yaw(yaw), m_Pitch(pitch), m_Zoom(zoom), m_Speed(SPEED), m_Sensitivity(SENSITIVITY), m_Position(position)
    {
    }

    virtual void Update() = 0;

    virtual glm::mat4 const ProjectionMatrix() const = 0;
    virtual glm::mat4 const ViewMatrix() const = 0;

    virtual void Move(const Direction) = 0;      // keyboard input
    virtual void Move(const double, double) = 0; // mouse position
    virtual void Move(const double) = 0;         // mouse scroll

    virtual void DrawDebugInfo() override;

    float GetYaw() const;
    void SetYaw(float);

    float GetPitch() const;
    void SetPitch(float);

    float GetZoom() const;
    void SetZoom(float);

    float GetSpeed() const;
    void SetSpeed(float);

    float GetSensitivity() const;
    void SetSensitivity(float);

    const glm::vec3 &GetPosition() const;
    void SetPosition(const glm::vec3 &);

    virtual ~Camera()
    {
    }

  protected:
    float m_Yaw;
    float m_Pitch;
    float m_Zoom;
    float m_Speed;
    float m_Sensitivity;
    glm::vec3 m_Position;
};

}; // namespace engine