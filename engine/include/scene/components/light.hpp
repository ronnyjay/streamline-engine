#pragma once

#include "math/vec4.hpp" // IWYU pragma: keep

namespace engine
{

struct Light
{
    explicit Light(const vec4 &color)
        : color(color)
    {
    }

    vec4 color;
};

} // namespace engine
