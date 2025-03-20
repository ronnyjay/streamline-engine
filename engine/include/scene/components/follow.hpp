#pragma once

#include "../entity.hpp"
#include "math/vec3.hpp"

namespace engine
{

struct Follow
{
    Follow(entity_type target, vec3 const &offset = vec3(0.0f))
        : target(target)
        , offset(offset)
    {
    }

    entity_type target;

    vec3        offset;

    float       yawDamping = 1.0f;
    float       pitchDamping = 1.0f;

    bool        b_ignoreYawRotation = false;
    bool        b_ignorePitchRotation = false;
};

} // namespace engine
