#pragma once

#include <engine/camera/camera.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace engine
{

namespace camera
{

class perspective_camera : public camera_t
{
  public:
    perspective_camera();

    virtual glm::mat4 const projection() const override;
    virtual glm::mat4 const view() const override;

    virtual void move(movement_direction) override;

  private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;

    float m_speed;
};
}; // namespace camera

} // namespace engine