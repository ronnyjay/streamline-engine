#pragma once

#include <engine/mesh/mesh.hpp>

namespace engine
{

namespace mesh
{

class pyramid : public mesh_t
{
  public:
    pyramid();

    void update(double);
    void draw(glm::mat4, glm::mat4);

  private:
    static const GLfloat m_data[][5];
};

}; // namespace mesh

}; // namespace engine