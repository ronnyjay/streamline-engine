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

template <int N, typename T> struct vec;

template <typename T> struct vec<3, T>
{
    // clang-format off
    
#if STREAMLINE_CONFIG_ANONYMOUS_STRUCT == STREAMLINE_ENABLE
    union 
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
        struct { T s, t, p; };

#       if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_OPERATOR
            STREAMLINE_SWIZZLE3_2MEMBERS(T, x, y, z)
            STREAMLINE_SWIZZLE3_2MEMBERS(T, r, g, b)
            STREAMLINE_SWIZZLE3_2MEMBERS(T, s, t, p)
            STREAMLINE_SWIZZLE3_3MEMBERS(T, x, y, z)
            STREAMLINE_SWIZZLE3_3MEMBERS(T, r, g, b)
            STREAMLINE_SWIZZLE3_3MEMBERS(T, s, t, p)
            STREAMLINE_SWIZZLE3_4MEMBERS(T, x, y, z)
            STREAMLINE_SWIZZLE3_4MEMBERS(T, r, g, b)
            STREAMLINE_SWIZZLE3_4MEMBERS(T, s, t, p)
#       endif
    };
#else
    union { T x, r, s; };
    union { T y, g, t; };
    union { T z, b, p; };

#   if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_FUNCTION
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC3(T, x, y, z)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC3(T, r, g, b)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC3(T, s, t, p)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC3(T, x, y, z)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC3(T, r, g, b)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC3(T, s, t, p)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC3(T, x, y, z)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC3(T, r, g, b)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC3(T, s, t, p)
#   endif
#endif

    // clang-format on

    vec()
        : x(T(0))
        , y(T(0))
        , z(T(0))
    {
    }

    vec(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    vec(T scalar)
        : x(scalar)
        , y(scalar)
        , z(scalar)
    {
    }

    size_t length() const
    {
        return 3;
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
        case 2:
            return z;
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
        case 2:
            return z;
        }
    }

    vec<3, T> &operator=(const vec<3, T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }

    vec<3, T> &operator+=(T s)
    {
        this->x += s;
        this->y += s;
        this->z += s;
    }

    vec<3, T> &operator+=(const vec<3, T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    vec<3, T> &operator-=(T s)
    {
        this->x -= s;
        this->y -= s;
        this->y -= s;
    }

    vec<3, T> &operator-=(const vec<3, T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    vec<3, T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
    }

    vec<3, T> &operator*=(const vec<3, T> &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    vec<3, T> &operator/=(T s)
    {
        this->x /= s;
        this->y /= s;
        this->z /= s;
    }

    vec<3, T> &operator/=(const vec<3, T> &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        return *this;
    }

    bool operator==(const vec<3, T> &other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator!=(const vec<3, T> &other) const
    {
        return this->x != other.x || this->y != other.y || this->z != other.z;
    }
};

template <typename T> vec<3, T> operator+(vec<3, T> const &v, T s)
{
    return vec<3, T>(v.x + s, v.y + s, v.z + s);
}

template <typename T> vec<3, T> operator+(vec<3, T> const &v1, vec<3, T> const &v2)
{
    return vec<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T> vec<3, T> operator-(vec<3, T> const &v)
{
    return vec<3, T>(-v.x, -v.y, -v.z);
}

template <typename T> vec<3, T> operator-(vec<3, T> const &v, T s)
{
    return vec<3, T>(v.x - s, v.y - s, v.z - s);
}

template <typename T> vec<3, T> operator-(vec<3, T> const &v1, vec<3, T> const &v2)
{
    return vec<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T> vec<3, T> operator*(vec<3, T> const &v, T s)
{
    return vec<3, T>(v.x * s, v.y * s, v.z * s);
}

template <typename T> vec<3, T> operator*(vec<3, T> const &v1, vec<3, T> const &v2)
{
    return vec<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T> vec<3, T> operator/(vec<3, T> const &v, T s)
{
    return vec<3, T>(v.x / s, v.y / s, v.z / s);
}

template <typename T> vec<3, T> operator/(vec<3, T> const &v1, vec<3, T> const &v2)
{
    return vec<3, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
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