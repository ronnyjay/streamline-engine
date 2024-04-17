#include <engine/world/world.hpp>

using namespace engine;

extern int window_width;
extern int window_height;

world::world()
{
}

void world::update(double dt)
{
    for (auto obj : m_meshes)
    {
        obj->update(dt);
    }
}

void world::draw()
{
    for (auto obj : m_meshes)
    {

        obj->draw(m_camera.projection(), m_camera.view());
    }
}

void world::add_mesh(engine::mesh::mesh_t *const obj)
{
    m_meshes.push_back(obj);
}
