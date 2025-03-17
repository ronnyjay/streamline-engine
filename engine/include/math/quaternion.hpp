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
    mat<4, 4, T> result(T(1));

    T            xx = q.x * q.x;
    T            yy = q.y * q.y;
    T            zz = q.z * q.z;
    T            xy = q.x * q.y;
    T            xz = q.x * q.z;
    T            yz = q.y * q.z;
    T            wx = q.w * q.x;
    T            wy = q.w * q.y;
    T            wz = q.w * q.z;

    result[0][0] = 1 - 2 * (yy + zz);
    result[1][0] = 2 * (xy - wz);
    result[2][0] = 2 * (xz + wy);
    result[3][0] = 0;

    result[0][1] = 2 * (xy + wz);
    result[1][1] = 1 - 2 * (xx + zz);
    result[2][1] = 2 * (yz - wx);
    result[3][1] = 0;

    result[0][2] = 2 * (xz - wy);
    result[1][2] = 2 * (yz + wx);
    result[2][2] = 1 - 2 * (xx + yy);
    result[3][2] = 0;

    result[0][3] = 0;
    result[1][3] = 0;
    result[2][3] = 0;
    result[3][3] = 1;

    return result;
}

} // namespace engine