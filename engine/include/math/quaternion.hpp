#pragma once

#include "trigonometric.hpp"

#include "mat4x4.hpp" // IWYU pragma: keep
#include "vec3.hpp"   // IWYU pragma: keep

namespace engine
{

template <typename T>
struct quat
{
    quat(T w = T(1), T x = T(0), T y = T(0), T z = T(0))
        : w(w)
        , x(x)
        , y(y)
        , z(z)
    {
    }

    quat(const vec<3, T> &eulerAngles)
    {
        vec<3, T> c = cos(eulerAngles * T(0.5));
        vec<3, T> s = sin(eulerAngles * T(0.5));

        w = c.x * c.y * c.z + s.x * s.y * s.z;
        x = s.x * c.y * c.z - c.x * s.y * s.z;
        y = c.x * s.y * c.z + s.x * c.y * s.z;
        z = c.x * c.y * s.z - s.x * s.y * c.z;
    }

    T w, x, y, z;
};

template <typename T = float>
inline mat<4, 4, T> toMat4(const quat<T> &q)
{
    mat<4, 4, T> result(1.0f);

    result[0][0] = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
    result[0][1] = 2 * q.x * q.y + 2 * q.z * q.w;
    result[0][2] = 2 * q.x * q.z - 2 * q.y * q.w;
    result[0][3] = 0.0f;

    result[1][0] = 2 * q.x * q.y + 2 * q.z * q.w;
    result[1][1] = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
    result[1][2] = 2 * q.y * q.y - 2 * q.x * q.w;
    result[1][3] = 0.0f;

    result[2][0] = 2 * q.x * q.z - 2 * q.y * q.w;
    result[2][1] = 2 * q.y * q.z + 2 * q.x * q.w;
    result[2][2] = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
    result[2][3] = 0.0f;

    return result;
}

} // namespace engine