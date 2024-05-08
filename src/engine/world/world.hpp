#pragma once

#include <engine/debug/debug.hpp>
#include <engine/mesh/mesh.hpp>

#include <list>

namespace engine
{

class World : public Debuggable
{
  public:
    World(const std::string &identifier) : Debuggable(identifier)
    {
    }

    void update(double);
    void draw();

    void add_mesh(Mesh *const);

    virtual void draw_debug_info() override;

  private:
    std::list<Mesh *> m_meshes;
};

}; // namespace engine
