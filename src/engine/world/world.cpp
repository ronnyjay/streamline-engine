#include <engine/world/world.hpp>

using namespace engine;

extern int window_width;
extern int window_height;

extern engine::camera::orthographic_camera perspective_camera;

engine::world::world()
{
}

void engine::world::update(double dt)
{
    for (auto obj : m_meshes)
    {
        obj->update(dt);
    }
}

void engine::world::draw()
{
    for (auto obj : m_meshes)
    {

        obj->draw(perspective_camera.projection(), perspective_camera.view());
    }
}

void engine::world::add_mesh(engine::mesh::mesh_t *const obj)
{
    m_meshes.push_back(obj);
}
