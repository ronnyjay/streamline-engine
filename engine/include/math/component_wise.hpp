#pragma once

#include "assert.hpp"

#include "detail/type_vec2.hpp" // IWYU pragma: keep
#include "detail/type_vec3.hpp" // IWYU pragma: keep
#include "detail/type_vec4.hpp" // IWYU pragma: keep

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>

namespace engine
{

template <typename T>
STREAMLINE_INLINE vec<2, T> abs(const vec<2, T> &v)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'abs' accepts only floating-point inputs");
  return vec<2, T>(std::abs(v.x), std::abs(v.y));
}

template <typename T>
STREAMLINE_INLINE vec<3, T> abs(const vec<3, T> &v)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'abs' accepts only floating-point inputs");
  return vec<3, T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
STREAMLINE_INLINE vec<4, T> abs(const vec<4, T> &v)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'abs' accepts only floating-point inputs");
  return vec<4, T>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
}

template <typename T>
STREAMLINE_INLINE vec<2, T> min(const vec<2, T> &v1, const vec<2, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'min' accepts only floating-point inputs");
  return vec<2, T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}

template <typename T>
STREAMLINE_INLINE vec<3, T> min(const vec<3, T> &v1, const vec<3, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'min' accepts only floating-point inputs");
  return vec<3, T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
}

template <typename T>
STREAMLINE_INLINE vec<4, T> min(const vec<4, T> &v1, const vec<4, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'min' accepts only floating-point inputs");
  return vec<4, T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z), std::min(v1.w, v2.w));
}

template <typename T>
STREAMLINE_INLINE vec<2, T> max(const vec<2, T> &v1, const vec<2, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'max' accepts only floating-point inputs");
  return vec<2, T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}

template <typename T>
STREAMLINE_INLINE vec<3, T> max(const vec<3, T> &v1, const vec<3, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'max' accepts only floating-point inputs");
  return vec<3, T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
}

template <typename T>
STREAMLINE_INLINE vec<4, T> max(const vec<4, T> &v1, const vec<4, T> &v2)
{
  STREAMLINE_ASSERT(std::numeric_limits<T>::is_iec559, "'max' accepts only floating-point inputs");
  return vec<4, T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z), std::max(v1.w, v2.w));
}

} // namespace engine
