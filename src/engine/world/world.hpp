#pragma once

#define GLFW_INCLUDE_NONE

#include <engine/camera/orthographic/orthographic.hpp>
#include <engine/camera/perspective/perspective.hpp>
#include <engine/mesh/mesh.hpp>

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

    void show_wireframes(bool);

  private:
    std::list<engine::mesh::mesh_t *> m_meshes;
};

}; // namespace engine
