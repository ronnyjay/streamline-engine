#include "core/logger.hpp"
#include "math/ext/vector_float4.hpp"
#include "math/transformation.hpp"
#include "math/trigonometric.hpp"
#include "scene/components/orbit.hpp"
#include "scene/scene.hpp"
#include <cmath>

using namespace engine;

void FollowSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<Follow, Transform>();

    for (const auto &entity : view)
    {
        auto [follow, transform] = view.get(entity);

        if (auto *target = m_scene->m_registry.try_get<Transform>(follow.target))
        {

            // Not quite sure if this should be a part of the follow system
            // It is possible that this would best fit into the camera system
            if (auto *orbit = m_scene->m_registry.try_get<Orbit>(entity))
            {
                vec3 offset      = vec3(0.0f, 0.0f, -orbit->distance); // negate distance to ensure forward direction
                mat4 pitchMatrix = rotate(mat4(1.0f), radians(-transform.rotation.x), vec3(1.0f, 0.0f, 0.0f));
                mat4 yawMatrix   = rotate(mat4(1.0f), radians(-transform.rotation.y), vec3(0.0f, 1.0f, 0.0f));
                offset           = (yawMatrix * pitchMatrix * vec4(offset, 1.0f)).xyz();

                transform.translation = target->translation + offset;
            }
            else
            {
                transform.translation = target->translation + follow.offset;
            }

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