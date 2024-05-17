#include <engine/application/application.hpp>
#include <engine/world/world.hpp>

#include <set>

using namespace engine;

extern Application application;

void World::update(double dt)
{
    std::set<Object *> collisions;

    // Check for collisions between all objects in scene
    // This should eventually be reworked, but for now it does what's needed.
    for (auto it = m_meshes.begin(); it != m_meshes.end(); ++it)
    {
        (*it)->update(dt);

        // Collisions between meshes
        auto it2 = it;
        ++it2;
        while (it2 != m_meshes.end())
        {
            if (check_collision(static_cast<Object *>(*it), static_cast<Object *>(*it2)))
            {
                collisions.insert(static_cast<Object *>(*it));
                collisions.insert(static_cast<Object *>(*it2));
            }
            ++it2;
        }

        // Collision between children & meshes
        for (auto &child : (*it)->children())
        {
            for (auto &other : m_meshes)
            {
                if (check_collision(static_cast<Object *>(child), static_cast<Object *>(other)))
                {
                    collisions.insert(static_cast<Object *>(child));
                    collisions.insert(static_cast<Object *>(other));
                }
            }
        }
    }

    // Trigger collision callbacks
    for (auto &mesh : m_meshes)
    {
        auto object = static_cast<Object *>(mesh);
        bool collided = (collisions.find(object) != collisions.end());

        if (collided)
        {
            object->trigger_collision();
        }
        else
        {
            object->trigger_collision_resolve();
        }

        for (auto &child : object->children())
        {
            auto child_object = static_cast<Object *>(child);
            bool child_collided = (collisions.find(static_cast<Object *>(child)) != collisions.end());

            if (child_collided)
            {
                child_object->trigger_collision();
            }
            else
            {
                child_object->trigger_collision_resolve();
            }
        }
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

bool World::check_collision(const Object *object, const glm::vec3 &point)
{
    auto object_min = object->bounding_box().min();
    auto object_max = object->bounding_box().max();

    if (point.x >= object_min.x && point.x <= object_max.x && point.y >= object_min.y && point.y <= object_max.y && point.z >= object_min.z &&
        point.z <= object_max.z)
    {
        return true;
    }

    return false;
}

bool World::check_collision(const Object *a, const Object *b)
{
    Vertex a_min = a->bounding_box().min();
    Vertex a_max = a->bounding_box().max();

    Vertex b_min = b->bounding_box().min();
    Vertex b_max = b->bounding_box().max();

    bool overlap_x = (a_min.x <= b_max.x) && (a_max.x >= b_min.x);
    bool overlap_y = (a_min.y <= b_max.y) && (a_max.y >= b_min.y);
    bool overlap_z = (a_min.z <= b_max.z) && (a_max.z >= b_min.z);

    if (overlap_x && overlap_y && overlap_z)
    {
        return true;
    }

    return false;
}