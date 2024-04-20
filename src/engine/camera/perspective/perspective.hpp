#pragma once

#include <engine/camera/camera.hpp>

namespace engine
{

namespace camera
{

class perspective_camera : public camera_t
{
  public:
    perspective_camera();

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_projection_matrix() const override;

    virtual void update() override;
    virtual void move(movement_direction) override;
    virtual void move(float xoffset, float yoffset) override;
    virtual void move(float yoffset) override;

  private:
    glm::vec3 m_direction;
    glm::vec3 m_forward_horizontal; // ensure camera moves along the horizontal plane
    glm::vec3 m_up;
    glm::vec3 m_world_up;
    glm::vec3 m_right;

    float m_yaw;
    float m_pitch;
};
}; // namespace camera

} // namespace engine