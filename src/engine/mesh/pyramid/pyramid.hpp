#pragma once

#include <engine/mesh/mesh.hpp>
#include <string>

namespace engine
{

namespace mesh
{

class pyramid : public mesh_t
{
  public:
    pyramid(const std::basic_string<char> &name);

    void update(double);
    void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &);

  private:
    glm::mat4 m_local_model;

    static const GLfloat m_data[][5];
};

}; // namespace mesh

}; // namespace engine