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

    virtual void update() override;

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_matrix() const override;

    virtual void move(direction) override;                    // keyboard input
    virtual void move(float xoffset, float yoffset) override; // mouse movement
    virtual void move(float yoffset) override;                // mouse scroll

  private:
    glm::mat4 m_view_model;
};

}; // namespace camera

}; // namespace engine