#pragma once

#include <cmath>

#include "detail/type_vec2.hpp"
#include "detail/type_vec3.hpp"
#include "detail/type_vec4.hpp"

namespace engine
{

static float radians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}

static float degrees(float radians)
{
    return radians * (180 * M_1_PI);
}

template <typename T>
vec<2, T> sin(vec<2, T> const &v)
{
    return vec<2, T>(sin(v.x), sin(v.y));
}

template <typename T>
vec<2, T> cos(vec<2, T> const &v)
{
    return vec<2, T>(cos(v.x), cos(v.y));
}

template <typename T>
vec<3, T> sin(vec<3, T> const &v)
{
    return vec<3, T>(sin(v.x), sin(v.y), sin(v.z));
}

template <typename T>
vec<3, T> cos(vec<3, T> const &v)
{
    return vec<3, T>(cos(v.x), cos(v.y), cos(v.z));
}

template <typename T>
vec<4, T> sin(vec<4, T> const &v)
{
    return vec<4, T>(sin(v.x), sin(v.y), sin(v.z), sin(v.w));
}

template <typename T>
vec<4, T> cos(vec<4, T> const &v)
{
    return vec<4, T>(cos(v.x), cos(v.y), cos(v.z), cos(v.w));
}

} // namespace engine