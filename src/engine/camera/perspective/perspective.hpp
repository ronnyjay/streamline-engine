#pragma once

#include <engine/camera/camera.hpp>

namespace engine
{

class PerspectiveCamera : public Camera
{
  public:
    PerspectiveCamera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 90.0f, float pitch = PITCH)
        : Camera("Perspective Camera", position, yaw, pitch, 45.0f), m_front(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f), m_world_up(m_up),
          m_lock_horizontal_movement(false)
    {
        update_vectors();
    }

    virtual void update_vectors() override;

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_matrix() const override;

    virtual void move(const CameraDirection) override; // keyboard input
    virtual void move(const double, double) override;  // mouse movement
    virtual void move(const double) override;          // mouse scroll

    virtual void draw_debug_info() override;

    void lock_horizontal_movement(const bool);

  private:
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    glm::vec3 m_forward_horizontal;
    bool m_lock_horizontal_movement;
};

}; // namespace engine