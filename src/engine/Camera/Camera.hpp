#pragma once

#include <engine/Debug/Debuggable.hpp>

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
const float SPEED = 10.0f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 1.0f;

class Camera : public Debuggable
{
  public:
    Camera(
        const glm::vec3 position = glm::vec3(0.0f),
        const float yaw = YAW,
        const float pitch = PITCH,
        const float zoom = ZOOM)
        : m_Yaw(yaw)
        , m_Pitch(pitch)
        , m_Zoom(zoom)
        , m_Speed(SPEED)
        , m_Sensitivity(SENSITIVITY)
        , m_Position(position)
    {
    }

    virtual void Update() = 0;

    virtual glm::mat4 const ProjectionMatrix() const = 0;
    virtual glm::mat4 const ViewMatrix() const = 0;

    virtual void Move(const Direction, double) = 0; // keyboard input
    virtual void Move(double, double) = 0;          // mouse position
    virtual void Move(double) = 0;                  // mouse scroll

    virtual void DrawDebugInfo() override;

    float GetYaw() const;
    void SetYaw(const float);

    float GetPitch() const;
    void SetPitch(const float);

    float GetZoom() const;
    void SetZoom(const float);

    float GetSpeed() const;
    void SetSpeed(const float);

    float GetSensitivity() const;
    void SetSensitivity(const float);

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

} // namespace engine