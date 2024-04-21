#pragma once

#include <engine/mesh/mesh.hpp>
#include <glm/fwd.hpp>

namespace engine
{

namespace mesh
{

class rectangle : public mesh_t
{
  public:
    rectangle(const std::basic_string<char> &name);

    virtual void update(double) override;
    virtual void draw(const glm::mat4&, const glm::mat4&, const glm::mat4&) override;

  private:
    static const GLfloat m_data[4][5];
};

}; // namespace mesh

}; // namespace engine
