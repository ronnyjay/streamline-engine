#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace engine
{

namespace camera
{

typedef enum
{
    forward,
    backward,
    left,
    right
} movement_direction;

class camera_t
{
  public:
    camera_t() = default;

    virtual glm::mat4 const projection() const = 0;
    virtual glm::mat4 const view() const = 0;

    virtual void move(movement_direction) = 0;

    ~camera_t() = default;

  private:
};

} // namespace camera

}; // namespace engine