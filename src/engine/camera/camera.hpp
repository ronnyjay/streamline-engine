#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace engine
{

class camera
{
  public:
    camera();
    camera(glm::vec3, glm::vec3, glm::vec3);

    glm::mat4 const projection() const;
    glm::mat4 const view() const;

  private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;
};

}; // namespace engine