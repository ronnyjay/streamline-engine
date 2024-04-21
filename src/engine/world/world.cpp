#include <engine/world/world.hpp>

#include <imgui.h>

using namespace engine;

extern int window_width;
extern int window_height;

extern engine::camera::perspective_camera global_camera;

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
        obj->draw(glm::mat4(0), global_camera.projection_matrix(), global_camera.view_matrix());
    }

    if (ImGui::TreeNode("Objects"))
    {
        for (auto obj : m_meshes)
        {
            obj->draw_imgui();
        }

        ImGui::TreePop();
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
