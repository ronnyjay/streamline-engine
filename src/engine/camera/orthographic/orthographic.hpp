#pragma once

#include <engine/camera/camera.hpp>

namespace engine
{

class OrthographicCamera : public Camera
{
  public:
    OrthographicCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
        : Camera("Orthographic Camera", position, yaw, pitch, zoom)
    {
        update_vectors();
    }

    virtual void update_vectors() override;

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_matrix() const override;

    virtual void move(const CameraDirection) override; // keyboard input
    virtual void move(const double, double) override;  // mouse movement
    virtual void move(const double) override;          // mouse scroll

  private:
    glm::mat4 m_view_model;
};

}; // namespace engine