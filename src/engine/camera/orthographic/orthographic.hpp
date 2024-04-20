#pragma once

#include <engine/camera/camera.hpp>

namespace engine
{

namespace camera
{

class orthographic_camera : public camera_t
{
  public:
    orthographic_camera();

    virtual glm::mat4 const projection() const override;
    virtual glm::mat4 const view() const override;

    virtual void move(movement_direction) override;

  private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;

    float m_speed;
    float m_scale;
};

}; // namespace camera

}; // namespace engine