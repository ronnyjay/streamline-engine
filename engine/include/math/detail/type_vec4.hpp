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
struct vec<4, T>
{
    // clang-format off

#if STREAMLINE_CONFIG_ANONYMOUS_STRUCT == STREAMLINE_ENABLE
    union 
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };

#       if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_OPERATOR
            STREAMLINE_SWIZZLE4_2MEMBERS(T, x, y, z, w)
            STREAMLINE_SWIZZLE4_2MEMBERS(T, r, g, b, a)
            STREAMLINE_SWIZZLE4_2MEMBERS(T, s, t, p, q)
            STREAMLINE_SWIZZLE4_3MEMBERS(T, x, y, z, w)
            STREAMLINE_SWIZZLE4_3MEMBERS(T, r, g, b, a)
            STREAMLINE_SWIZZLE4_3MEMBERS(T, s, t, p, q)
            STREAMLINE_SWIZZLE4_4MEMBERS(T, x, y, z, w)
            STREAMLINE_SWIZZLE4_4MEMBERS(T, r, g, b, a)
            STREAMLINE_SWIZZLE4_4MEMBERS(T, s, t, p, q)
#       endif
    };
#else
    union { T x, r, s; };
    union { T y, g, t; };
    union { T z, b, p; };
    union { T w, a, q; };

#   if STREAMLINE_CONFIG_SWIZZLE == STREAMLINE_SWIZZLE_FUNCTION
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC4(T, x, y, z, w)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC4(T, r, g, b, a)
        STREAMLINE_SWIZZLE_GEN_VEC2_FROM_VEC4(T, s, t, p, q)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC4(T, x, y, z, w)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC4(T, r, g, b, a)
        STREAMLINE_SWIZZLE_GEN_VEC3_FROM_VEC4(T, s, t, p, q)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC4(T, x, y, z, w)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC4(T, r, g, b, a)
        STREAMLINE_SWIZZLE_GEN_VEC4_FROM_VEC4(T, s, t, p, q)
#   endif
#endif

    // clang-format on

    vec()
        : x(T(0))
        , y(T(0))
        , z(T(0))
        , w(T(0))
    {
    }

    vec(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    vec(vec<2, T> const &v, T z, T w)
        : x(v.x)
        , y(v.y)
        , z(z)
        , w(w)
    {
    }

    vec(vec<3, T> const &v, T w)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(w)
    {
    }

    vec(T scalar)
        : x(scalar)
        , y(scalar)
        , z(scalar)
        , w(scalar)
    {
    }

    size_t length() const
    {
        return 4;
    }

    /**
     * @brief
     *
     * @param index
     * @return T&
     */
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
        case 3:
            return w;
        }
    }

    /**
     * @brief
     *
     * @param index
     * @return const T&
     */
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
        case 3:
            return w;
        }
    }

    vec<4, T> &operator=(const vec<4, T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
        return *this;
    }

    vec<4, T> &operator+=(T s)
    {
        this->x += s;
        this->y += s;
        this->z += s;
        this->w += s;
    }

    vec<4, T> &operator+=(const vec<4, T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
        return *this;
    }

    vec<4, T> &operator-=(T s)
    {
        this->x -= s;
        this->y -= s;
        this->z -= s;
        this->w -= s;
    }

    vec<4, T> &operator-=(const vec<4, T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
        return *this;
    }

    vec<4, T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        this->w *= s;
    }

    vec<4, T> &operator*=(const vec<4, T> &other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        this->w *= other.w;
        return *this;
    }

    vec<4, T> &operator/=(T s)
    {
        this->x /= s;
        this->y /= s;
        this->z /= s;
        this->w /= s;
    }

    vec<4, T> &operator/=(const vec<4, T> &other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        this->w /= other.w;
        return *this;
    }

    bool operator==(const vec<4, T> &other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
    }

    bool operator!=(const vec<4, T> &other) const
    {
        return this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w;
    }
};

template <typename T>
vec<4, T> operator+(vec<4, T> const &v, T s)
{
    return vec<4, T>(v.x + s, v.y + s, v.z + s, v.w + s);
}

template <typename T>
vec<4, T> operator+(vec<4, T> const &v1, vec<4, T> const &v2)
{
    return vec<4, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
vec<4, T> operator-(vec<4, T> const &v, T s)
{
    return vec<4, T>(v.x - s, v.y - s, v.z - s, v.w - s);
}

template <typename T>
vec<4, T> operator-(vec<4, T> const &v1, vec<4, T> const &v2)
{
    return vec<4, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
vec<4, T> operator*(vec<4, T> const &v, T s)
{
    return vec<4, T>(v.x * s, v.y * s, v.z * s, v.w * s);
}

template <typename T>
vec<4, T> operator*(vec<4, T> const &v1, vec<4, T> const &v2)
{
    return vec<4, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
vec<4, T> operator/(vec<4, T> const &v, T s)
{
    return vec<4, T>(v.x / s, v.y / s, v.z / s, v.w / s);
}

template <typename T>
vec<4, T> operator/(vec<4, T> const &v1, vec<4, T> const &v2)
{
    return vec<4, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
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