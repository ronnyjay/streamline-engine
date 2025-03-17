#include "scene/systems/follow_system.hpp"
#include "scene/scene.hpp"

using namespace engine;

void FollowSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<Follow, Transform>();

    for (const auto &entity : view)
    {
        auto [follow, transform] = view.get(entity);

        printf("FollowEntity: %d\n", follow.id);
        printf("IgnorePitch: %d\n", follow.b_ignorePitchRotation);
        printf("IgnoreYaw: %d\n", follow.b_ignoreYawRotation);

        if (auto *target = m_scene->m_registry.try_get<Transform>(follow.target))
        {
            transform.translation = target->translation + follow.offset;

            if (!follow.b_ignorePitchRotation)
            {
                transform.rotation.x = target->rotation.x;
            }
            else
            {
                // printf("ignorning pitch for %d\n", follow.id);
            }

            if (!follow.b_ignoreYawRotation)
            {
                transform.rotation.y = target->rotation.y;
            }
            else
            {
                // printf("ignoring yaw for %d\n", follow.id);
            }
        }
    }
}