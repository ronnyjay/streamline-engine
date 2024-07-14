#pragma once

#include <engine/Components/AABB.hpp>
#include <engine/Components/BSphere.hpp>

#include <variant>

namespace engine
{

typedef std::variant<AABB, BSphere> BoundingVolume;

}
