#pragma once

#include <engine/mesh/mesh.hpp>

namespace engine
{

namespace mesh
{

class rectangle : public mesh_t
{
  public:
    rectangle();

    virtual void update(double) override;
    virtual void draw(glm::mat4, glm::mat4) override;

  private:
    static const GLfloat m_data[4][5];
};

}; // namespace mesh

}; // namespace engine
