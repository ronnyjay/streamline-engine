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
        static int unique_id = 1;
        id = unique_id++;
    }

    int         id;
    entity_type target;

    vec3        offset;

    bool        b_ignoreYawRotation = false;
    bool        b_ignorePitchRotation = false;
};

} // namespace engine
