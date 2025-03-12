#pragma once

#include "assert.hpp"

#include "detail/type_vec2.hpp" // IWYU pragma: keep
#include "detail/type_vec3.hpp" // IWYU pragma: keep
#include "detail/type_vec4.hpp" // IWYU pragma: keep

#include <cmath>
#include <limits>

namespace engine
{

template <typename T>
STREAMLINE_INLINE T length(const vec<2, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");
    return std::sqrt(dot(v, v));
}

template <typename T>
STREAMLINE_INLINE T length(const vec<3, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");
    return std::sqrt(dot(v, v));
}

template <typename T>
STREAMLINE_INLINE T length(const vec<4, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");
    return std::sqrt(dot(v, v));
}

template <typename T>
STREAMLINE_INLINE T dot(const vec<2, T> &a, const vec<2, T> &b)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
    return a.x * b.x + a.y * b.y;
}

template <typename T>
STREAMLINE_INLINE T dot(const vec<3, T> &a, const vec<3, T> &b)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
STREAMLINE_INLINE T dot(const vec<4, T> &a, const vec<4, T> &b)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
STREAMLINE_INLINE vec<3, T> cross(const vec<3, T> &a, const vec<3, T> &b)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'cross' accepts only floating-point inputs");
    return vec<3, T>((a.y * b.z) - (b.y * a.z), (a.z * b.x) - (b.z * a.x), (a.x * b.y) - (b.x * a.y));
}

template <typename T>
STREAMLINE_INLINE vec<2, T> normalize(const vec<2, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");
    return v * (static_cast<T>(1) / std::sqrt(dot(v, v)));
}

template <typename T>
STREAMLINE_INLINE vec<3, T> normalize(const vec<3, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");
    return v * (static_cast<T>(1) / std::sqrt(dot(v, v)));
}

template <typename T>
STREAMLINE_INLINE vec<4, T> normalize(const vec<4, T> &v)
{
    STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");
    return v * (static_cast<T>(1) / std::sqrt(dot(v, v)));
}

} // namespace engine