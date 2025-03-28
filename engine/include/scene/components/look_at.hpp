#pragma once

#include "scene/entity.hpp"

namespace engine
{

struct LookAt
{
    LookAt(entity_type target)
        : target(target)
    {
    }

    entity_type target;
};

} // namespace engine