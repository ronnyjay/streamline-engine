#include "scene/scene.hpp"

using namespace engine;

void CollisionSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<AABB, Transform>();

    for (const auto &entity : view)
    {
        auto [collider, transform] = view.get(entity);

        // collider.scale(transform.scale);
        // collider.rotate(transform.rotation);
        collider.translate(transform.translation);
    }
}