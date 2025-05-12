#pragma once

#include "math/geometric.hpp"
#include "math/quaternion.hpp"
#include "math/transformation.hpp"
#include "math/trigonometric.hpp"

namespace engine
{

struct Transform
{
    vec3       translation{0.0f, 0.0f, 0.0f};
    vec3       rotation{0.0f, 0.0f, 0.0f};
    vec3       scale{1.0f, 1.0f, 1.0f};

    const vec3 getFront() const
    {
        // 90 degrees added to yaw to ensure -Z forward axis
        // Add this here (and not to the rotation vector itself) to ensure that models are not rotated unnecessarily
        return vec3(::cos(radians(rotation.y + 90.0f)) * ::cos(radians(rotation.x)), ::sin(radians(rotation.x)),
                    ::sin(radians(rotation.y + 90.0f)) * ::cos(radians(rotation.x)));
    }

    const vec3 getRight() const
    {
        return normalize(cross(getFront(), vec3(0.0f, 1.0f, 0.0f)));
    }

    const vec3 getUp() const
    {
        return normalize(cross(getRight(), getFront()));
    }

    const mat4 getTransform() const
    {
        return translate(mat4(1.0f), translation) * toMat4(quat(rotation)) * engine::scale(mat4(1.0f), scale);
    }
};

} // namespace engine
