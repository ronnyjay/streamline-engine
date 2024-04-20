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

    virtual glm::mat4 const projection_matrix() const override;
    virtual glm::mat4 const view_projection_matrix() const override;

    virtual void update() override;
    virtual void move(movement_direction) override;
    virtual void move(float xoffset, float yoffset) override;
    virtual void move(float yoffset) override;

  private:
};

}; // namespace camera

}; // namespace engine