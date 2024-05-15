#include <engine/application/application.hpp>
#include <engine/world/world.hpp>

using namespace engine;

extern Application application;

void World::update(double dt)
{
    // basic collision testing between camera & objects
    glm::vec3 player_position = application.camera()->position();

    for (auto &mesh : m_meshes)
    {
        static_cast<Object *>(mesh)->check_collision(player_position);

        mesh->update(dt);
    }
}

void World::draw()
{
    for (auto &mesh : m_meshes)
    {
        mesh->draw(application.camera()->view_matrix(), glm::mat4(1.0f), application.camera()->projection_matrix());
    }
}

void World::draw_debug_info()
{
    if (ImGui::TreeNode("Meshes"))
    {
        for (const auto &mesh : m_meshes)
        {
            mesh->draw_debug_info();
        }

        ImGui::TreePop();
    }
}

void World::add_mesh(Mesh *const mesh)
{
    m_meshes.push_back(mesh);
}
