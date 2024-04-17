#pragma once

#include <engine/mesh/mesh.hpp>

#include <vector>

namespace engine
{

namespace mesh
{

class circle : public mesh_t
{
  public:
    circle();

    virtual void update(double) override;
    virtual void draw(glm::mat4, glm::mat4) override;

  private:
    std::vector<GLfloat> m_data;

    double m_rotation_angle;
    const double rotation_speed = 45.0; // degrees per second
};

}; // namespace mesh

}; // namespace engine