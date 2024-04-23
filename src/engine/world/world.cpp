#include <engine/camera/camera.hpp>
#include <engine/world/world.hpp>

extern int window_width;
extern int window_height;

extern engine::window application;

using namespace engine;

extern bool imGui_toggle;

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

void world::draw()
{

    for (auto obj : m_meshes)
    {
        obj->draw(glm::mat4(0), application.camera()->projection_matrix(), application.camera()->view_matrix());
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
