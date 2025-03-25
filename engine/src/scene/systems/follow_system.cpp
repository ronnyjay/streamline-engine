#include "scene/systems/follow_system.hpp"
#include "scene/scene.hpp"

using namespace engine;

void FollowSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<Follow, Transform>();

    for (const auto &entity : view)
    {
        auto [follow, transform] = view.get(entity);

        if (auto *target = m_scene->m_registry.try_get<Transform>(follow.target))
        {
            transform.translation = target->translation + follow.offset;

            if (!follow.b_ignorePitchRotation)
            {
                transform.rotation.x = target->rotation.x * follow.pitchDamping;

                if (follow.b_invertPitchRotation)
                {
                    transform.rotation.x = -transform.rotation.x;
                }
            }

            if (!follow.b_ignoreYawRotation)
            {
                transform.rotation.y = (target->rotation.y) * follow.yawDamping;

                if (follow.b_invertYawRotation)
                {
                    transform.rotation.y = -transform.rotation.y;
                }
            }
        }
    }
}