#pragma once

#include <engine/camera/camera.hpp>

namespace engine
{

class OrthographicCamera : public Camera
{
  public:
    OrthographicCamera(glm::vec3 position = glm::vec3(0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
        : Camera(position, yaw, pitch, zoom)
    {
        Update();
    }

    virtual void Update() override;

    virtual glm::mat4 const ProjectionMatrix() const override;
    virtual glm::mat4 const ViewMatrix() const override;

    virtual void Move(const Direction) override;         // keyboard input
    virtual void Move(const double, double) override {}; // mouse position
    virtual void Move(const double) override {};         // mouse scroll

  private:
    glm::mat4 m_ViewModel;
};

}; // namespace engine