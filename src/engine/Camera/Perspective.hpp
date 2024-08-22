#pragma once

#include <engine/Camera/Camera.hpp>

namespace engine
{

class PerspectiveCamera : public Camera
{
  public:
    PerspectiveCamera(
        const glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f),
        const float yaw = 90.0f,
        const float pitch = PITCH,
        const float zoom = 45.0f)
        : Camera(position, yaw, pitch, zoom)
        , m_Front(0.0f)
        , m_Up(0.0f, 1.0f, 0.0f)
        , m_WorldUp(m_Up)
        , m_LockHorizontal(false)
    {
        Update();
    }

    virtual void Update() override;

    virtual glm::mat4 const ProjectionMatrix() const override;
    virtual glm::mat4 const ViewMatrix() const override;

    virtual void Move(const Direction, double) override; // keyboard input
    virtual void Move(double, double) override;          // mouse position
    virtual void Move(double) override;                  // mouse scroll

    virtual void draw_debug_info() override;

    void LockHorizontal(const bool);

  private:
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_WorldUp;
    glm::vec3 m_Right;
    glm::vec3 m_ForwardHorizontal;
    bool m_LockHorizontal;
};

} // namespace engine