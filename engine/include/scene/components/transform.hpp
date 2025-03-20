#pragma once

#include "math/geometric.hpp"
#include "math/mat4x4.hpp"
#include "math/quaternion.hpp"
#include "math/transformation.hpp"
#include "math/trigonometric.hpp"
#include "math/vec3.hpp"

namespace engine
{

struct Transform
{
    vec3       translation{0.0f, 0.0f, 0.0f};
    vec3       rotation{0.0f, 0.0f, 0.0f};
    vec3       scale{1.0f, 1.0f, 1.0f};

    const vec3 getFront() const
    {
        return vec3(::cos(radians(rotation.y)) * ::cos(radians(rotation.x)), ::sin(radians(rotation.x)),
                    ::sin(radians(rotation.y)) * ::cos(radians(rotation.x)));
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
        return translate(mat4(1.0f), translation) * toMat4(quat(vec3(rotation.z, -rotation.y, rotation.x))) *
               engine::scale(mat4(1.0f), scale);
    }
};

} // namespace engine
