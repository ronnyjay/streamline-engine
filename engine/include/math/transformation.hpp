#pragma once

#include "geometric.hpp"

#include "detail/type_mat2x2.hpp"
#include "detail/type_mat3x3.hpp"
#include "detail/type_mat4x4.hpp"

#include <cmath>

namespace engine
{

template <typename T>
mat<4, 4, T> translate(mat<4, 4, T> const &m, vec<3, T> const &v)
{
    mat<4, 4, T> result(1.0f);

    result[3][0] = v.x;
    result[3][1] = v.y;
    result[3][2] = v.z;
    result[3][3] = 1.0f;

    return m * result;
}

template <typename T>
mat<4, 4, T> rotate(mat<4, 4, T> const &m, T angle, vec<3, T> const &axis)
{
    mat<4, 4, T> result(1.0f);

    result[0][0] = axis.x * axis.y * (1 - ::cos(angle)) + ::cos(angle);
    result[0][1] = axis.x * axis.y * (1 - ::cos(angle)) + axis.z * ::sin(angle);
    result[0][2] = axis.x * axis.z * (1 - ::cos(angle)) - axis.y * ::sin(angle);
    result[0][3] = 0.0f;

    result[1][0] = axis.y * axis.x * (1 - ::cos(angle)) - axis.z * ::sin(angle);
    result[1][1] = axis.y * axis.y * (1 - ::cos(angle)) + ::cos(angle);
    result[1][2] = axis.y * axis.x * (1 - ::cos(angle)) + axis.x * ::sin(angle);
    result[1][3] = 0.0f;

    result[2][0] = axis.z * axis.x * (1 - ::cos(angle)) + axis.y * ::sin(angle);
    result[2][1] = axis.z * axis.y * (1 - ::cos(angle)) - axis.x * ::sin(angle);
    result[2][2] = axis.z * axis.z * (1 - ::cos(angle)) + ::cos(angle);
    result[2][3] = 0.0f;

    return m * result;
}

template <typename T>
mat<4, 4, T> scale(mat<4, 4, T> const &m, vec<3, T> const &v)
{
    mat<4, 4, T> result(1.0f);

    result[0][0] = v[0];
    result[1][1] = v[1];
    result[2][2] = v[2];

    return m * result;
}

template <typename T>
mat<4, 4, T> inverse(mat<4, 4, T> const &m)
{
    T            coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    T            coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    T            coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

    T            coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    T            coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    T            coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

    T            coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    T            coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    T            coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

    T            coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    T            coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    T            coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

    T            coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    T            coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    T            coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

    T            coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    T            coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    T            coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    vec<4, T>    fac0 = (coef00, coef00, coef02, coef03);
    vec<4, T>    fac1 = (coef04, coef04, coef06, coef07);
    vec<4, T>    fac2 = (coef08, coef08, coef10, coef11);
    vec<4, T>    fac3 = (coef12, coef12, coef14, coef15);
    vec<4, T>    fac4 = (coef16, coef16, coef18, coef19);
    vec<4, T>    fac5 = (coef20, coef20, coef22, coef23);

    vec<4, T>    vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
    vec<4, T>    vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
    vec<4, T>    vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
    vec<4, T>    vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

    vec<4, T>    inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
    vec<4, T>    inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
    vec<4, T>    inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
    vec<4, T>    inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

    vec<4, T>    signA(+1, -1, +1, -1);
    vec<4, T>    signB(-1, +1, -1, +1);

    mat<4, 4, T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

    vec<4, T>    row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

    vec<4, T>    dot0(m[0] * row0);
    T            dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

    T            oneOverDeteterminant = static_cast<T>(1) / dot1;

    return inverse * oneOverDeteterminant;
}

template <typename T = float>
mat<4, 4, T> perspective(float fov, float aspect, float near, float far)
{
    mat<4, 4, T> result;

    result[0][0] = +(1 / (aspect * tan(fov / 2)));
    result[1][1] = +(1 / tan(fov / 2));
    result[2][2] = -((far + near) / (far - near));
    result[3][2] = -((2 * far * near) / (far - near));
    result[2][3] = -1;

    return result;
}

template <typename T = float>
mat<4, 4, T> ortho(float left, float right, float bottom, float top, float near, float far)
{
    mat<4, 4, T> result;
    result[0][0] = +(2 / (right - left));
    result[1][1] = +(2 / (top - bottom));
    result[2][2] = -(2 / (far - near));
    result[3][0] = -((right + left) / (right - left));
    result[3][1] = -((top + bottom) / (top - bottom));
    result[3][2] = -((far + near) / (far - near));
    return result;
}

template <typename T = float>
mat<4, 4, T> lookAt(vec<3, T> const &eye, vec<3, T> const &center, vec<3, T> const &up)
{
    vec<3, T>    f = normalize(center - eye);
    vec<3, T>    r = normalize(cross(f, up));
    vec<3, T>    u = cross(r, f);

    mat<4, 4, T> rotation(1.0f);
    rotation[0][0] = +r.x;
    rotation[1][0] = +r.y;
    rotation[2][0] = +r.z;
    rotation[0][1] = +u.x;
    rotation[1][1] = +u.y;
    rotation[2][1] = +u.z;
    rotation[0][2] = -f.x;
    rotation[1][2] = -f.y;
    rotation[2][2] = -f.z;

    mat<4, 4, T> translation = translate(mat<4, 4, T>(1.0f), -eye);

    return rotation * translation;
}

} // namespace engine