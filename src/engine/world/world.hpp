#pragma once

#include <engine/camera/camera.hpp>
#include <engine/mesh/mesh.hpp>

#include <glm/glm.hpp>

#include <list>

namespace engine
{

class world
{
  public:
    world();

    void update(double);
    void draw();
    void add_mesh(engine::mesh::mesh_t *const);

  private:
    camera m_camera;
    std::list<engine::mesh::mesh_t *> m_meshes;
};

}; // namespace engine
