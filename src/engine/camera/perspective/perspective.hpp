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

    virtual void update() override;

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_matrix() const override;

    virtual void move(direction) override;                    // keyboard input
    virtual void move(float xoffset, float yoffset) override; // mouse movement
    virtual void move(float yoffset) override;                // mouse scroll

  private:
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    glm::vec3 m_forward_horizontal;
};

}; // namespace camera

}; // namespace engine