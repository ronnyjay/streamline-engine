#pragma once

#include "assert.hpp"
#include "setup.hpp"

#include <cstddef>

// clang-format off
#if STREAMLINE_SILENT_WARNING == STREAMLINE_ENABLE
#   if STREAMLINE_COMPILER_GCC
#       pragma GCC diagnostic push
#       pragma GCC diagnostic ignored "-Wpedantic"
#       pragma GCC diagnostic ignored "-Wunknown-pragmas"
#   endif
#   if STREAMLINE_COMPILER_CLANG
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#       pragma clang diagnostic ignored "-Wnested-anon-types"
#       pragma clang diagnostic ignored "-Wpadded"
#   endif
#   if STREAMLINE_COMPILER_MSVC
#       pragma warning(push)
#       pragma warning(disable : 4201)
#   endif
#endif


#if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_OPERATOR
#   include "_swizzle.hpp"      // IWYU pragma: keep
#endif

#if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_FUNCTION
#   include "_swizzle_func.hpp" // IWYU pragma: keep
#endif
// clang-format on

namespace engine
{

template <int N, typename T>
struct vec;

template <typename T>
struct vec<2, T>
{
    // clang-format off
    
#if STREAMLINE_CONFIG_ANONYMOUS_STRUCT == STREAMLINE_ENABLE
    union
    {
        struct { T x, y; };
        struct { T r, g; };
        struct { T s, t; };

#       if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_OPERATOR
            STREAMLINE_SWIZZLE2_2MEMBERS(T, x, y)
            STREAMLINE_SWIZZLE2_2MEMBERS(T, r, g)
            STREAMLINE_SWIZZLE2_2MEMBERS(T, s, t)
            STREAMLINE_SWIZZLE2_3MEMBERS(T, x, y)
            STREAMLINE_SWIZZLE2_3MEMBERS(T, r, g)
            STREAMLINE_SWIZZLE2_3MEMBERS(T, s, t)
            STREAMLINE_SWIZZLE2_4MEMBERS(T, x, y)
            STREAMLINE_SWIZZLE2_4MEMBERS(T, r, g)
            STREAMLINE_SWIZZLE2_4MEMBERS(T, s, t)
#       endif  
    };
#else
    union { T x, r, s; };
    union { T y, g, t; };

#   if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_FUNCTION
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC2(T, x, y)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC2(T, r, g)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC2(T, s, t)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC2(T, x, y)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC2(T, r, g)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC2(T, s, t)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC2(T, x, y)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC2(T, r, g)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC2(T, s, t)
#    endif
#endif

    // clang-format on

    vec()
        : x(T(0))
        , y(T(0))
    {
    }

    vec(T x, T y)
        : x(x)
        , y(y)
    {
    }

    vec(T scalar)
        : x(scalar)
        , y(scalar)
    {
    }

    vec(const vec<2, T> &v)
        : x(v.x)
        , y(v.y)
    {
    }

    size_t length() const
    {
        return 2;
    }

    STREAMLINE_INLINE T &operator[](size_t index)
    {
        STREAMLINE_ASSERT_LENGTH(index, length());

        switch (index)
        {
        default:
        case 0:
            return x;
        case 1:
            return y;
        }
    }

    STREAMLINE_INLINE T const &operator[](size_t index) const
    {
        STREAMLINE_ASSERT_LENGTH(index, length());

        switch (index)
        {
        default:
        case 0:
            return x;
        case 1:
            return y;
        }
    }

    vec<2, T> &operator=(const vec<2, T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    vec<2, T> &operator+=(T s)
    {
        this->x += s;
        this->y += s;
    }

    vec<2, T> &operator+=(const vec<2, T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    vec<2, T> &operator-=(T s)
    {
        this->x -= s;
        this->y -= s;
    }

    vec<2, T> &operator-=(const vec<2, T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    vec<2, T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
    }

    vec<2, T> &operator*=(const vec<2, T> &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        return *this;
    }

    vec<2, T> &operator/=(T s)
    {
        this->x /= s;
        this->y /= s;
    }

    vec<2, T> &operator/=(const vec<2, T> &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        return *this;
    }

    bool operator==(const vec<2, T> &other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const vec<2, T> &other) const
    {
        return this->x != other.x || this->y != other.y;
    }
};

template <typename T>
vec<2, T> operator+(vec<2, T> const &v1, T s)
{
    return vec<2, T>(v1.x + s, v1.y + s);
}

template <typename T>
vec<2, T> operator+(vec<2, T> const &v1, vec<2, T> const &v2)
{
    return vec<2, T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
vec<2, T> operator-(vec<2, T> const &v1, T s)
{
    return vec<2, T>(v1.x - s, v1.y - s);
}

template <typename T>
vec<2, T> operator-(vec<2, T> const &v1, vec<2, T> const &v2)
{
    return vec<2, T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
vec<2, T> operator*(vec<2, T> const &v1, T s)
{
    return vec<2, T>(v1.x * s, v1.y * s);
}

template <typename T>
vec<2, T> operator*(vec<2, T> const &v1, vec<2, T> const &v2)
{
    return vec<2, T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
vec<2, T> operator/(vec<2, T> const &v1, T s)
{
    return vec<2, T>(v1.x / s, v1.y / s);
}

template <typename T>
vec<2, T> operator/(vec<2, T> const &v1, vec<2, T> const &v2)
{
    return vec<2, T>(v1.x / v2.x, v1.y / v2.y);
}

} // namespace engine

// clang-format off
#if STREAMLINE_SILENT_WARNING == STREAMLINE_ENABLE
#   if STREAMLINE_COMPILER_GCC
#       pragma GCC diagnostic pop
#   endif
#   if STREAMLINE_COMPILER_CLANG
#       pragma clang diagnostic pop
#   endif
#   if STREAMLINE_COMPILER_MSVC
#       pragma warning(pop)
#   endif
#endif
// clang-format on