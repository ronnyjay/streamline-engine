#include <engine/world/world.hpp>

using namespace engine;

extern int window_width;
extern int window_height;

extern engine::camera::orthographic_camera global_camera;

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

        obj->draw(global_camera.projection_matrix(), global_camera.view_projection_matrix());
    }
}

void engine::world::add_mesh(engine::mesh::mesh_t *const obj)
{
    m_meshes.push_back(obj);
}

void world::show_wireframes(bool val)
{
    val ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
