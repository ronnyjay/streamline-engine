#include "scene/systems/physics_system.hpp"
#include "scene/components/rigid_body.hpp"
#include "scene/scene.hpp"

using namespace engine;

void PhysicsSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<RigidBody, AABB, Transform>();

    for (auto const &entity : view)
    {
        auto [body, aabb, transform] = view.get(entity);

        vec3 accel;

        if (body.mass > 0)
        {
            accel += vec3(0.0f, -9.81f, 0.0f);
        }

        body.linearVelocity   = body.linearVelocity + accel * (float)dt;
        transform.translation = transform.translation + body.linearVelocity * (float)dt;
    }

    // check for collisions
    // not the most efficient way of doing this...
    for (auto a = view.begin(); a != view.end(); ++a)
    {
        for (auto b = std::next(a); b != view.end(); ++b)
        {
            auto &volumeA = view.get<AABB>(*a);
            auto &volumeB = view.get<AABB>(*b);
        }
    }
}