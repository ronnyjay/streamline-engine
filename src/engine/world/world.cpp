#include <engine/application/application.hpp>
#include <engine/world/world.hpp>

#include <set>

using namespace engine;

extern Application application;

void World::update(double dt)
{
    std::set<Object *> collidedObjects;

    // Update each object and check for collisions
    for (auto it = m_meshes.begin(); it != m_meshes.end(); ++it)
    {
        (*it)->update(dt);

        // check collisions between meshes
        auto it2 = it;
        ++it2;
        while (it2 != m_meshes.end())
        {
            if (check_collision(static_cast<Object *>(*it), static_cast<Object *>(*it2)))
            {
                collidedObjects.insert(static_cast<Object *>(*it));
                collidedObjects.insert(static_cast<Object *>(*it2));
            }
            ++it2;
        }

        // check collisions between this object's children and all other meshes
        for (auto &child : (*it)->children())
        {
            for (auto &other : m_meshes)
            {
                if (check_collision(static_cast<Object *>(child), static_cast<Object *>(other)))
                {
                    collidedObjects.insert(static_cast<Object *>(child));
                    collidedObjects.insert(static_cast<Object *>(other));
                }
            }
        }
    }

    // set collision status
    for (auto &mesh : m_meshes)
    {
        auto obj = static_cast<Object *>(mesh);
        bool collided = (collidedObjects.find(obj) != collidedObjects.end());
        obj->on_hit_callback(collided);

        for (auto &child : obj->children())
        {
            bool childCollided = (collidedObjects.find(static_cast<Object *>(child)) != collidedObjects.end());
            static_cast<Object *>(child)->on_hit_callback(childCollided);
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
    auto object_min = object->m_AABB.min();
    auto object_max = object->m_AABB.max();

    if (point.x >= object_min.x && point.x <= object_max.x && point.y >= object_min.y && point.y <= object_max.y && point.z >= object_min.z &&
        point.z <= object_max.z)
    {
        return true;
    }

    return false;
}

bool World::check_collision(const Object *a, const Object *b)
{
    auto a_min = a->m_AABB.min();
    auto a_max = a->m_AABB.max();
    auto b_min = b->m_AABB.min();
    auto b_max = b->m_AABB.max();

    // Check for overlap in each dimension
    bool overlapX = (a_min.x <= b_max.x) && (a_max.x >= b_min.x);
    bool overlapY = (a_min.y <= b_max.y) && (a_max.y >= b_min.y);
    bool overlapZ = (a_min.z <= b_max.z) && (a_max.z >= b_min.z);

    if (overlapX && overlapY && overlapZ)
    {
        return true;
    }

    return false;
}