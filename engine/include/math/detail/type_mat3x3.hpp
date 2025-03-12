#pragma once

#include "type_vec3.hpp"

namespace engine
{

template <int M, int N, typename T>
struct mat;

template <typename T>
struct mat<3, 3, T>
{
    // clang-format off
    static constexpr size_t length() { return 3; }
    // clang-format on

    typedef vec<3, T> col_type;
    typedef vec<3, T> row_type;

  private:
    col_type value[3];

  public:
    mat() = default;

    mat(T scalar)
    {
        value[0] = col_type(scalar, T(0), T(0));
        value[1] = col_type(T(0), scalar, T(0));
        value[2] = col_type(T(0), T(0), scalar);
    }

    // clang-format off
    mat(T const &x1, T const &y1, T const &z1, 
        T const &x2, T const &y2, T const &z2, 
        T const &x3, T const &y3, T const &z3)
    {
        value[0] = col_type(x1, y1, z1);
        value[1] = col_type(x2, y2, z2);
        value[2] = col_type(x3, y3, z3);
    }

    mat(col_type const &v1, 
        col_type const &v2, 
        col_type const &v3)
    {
        value[0] = v1;
        value[1] = v2;
        value[2] = v3;
    }
    // clang-format on

    mat<3, 3, T> &operator=(mat<3, 3, T> const &m)
    {
        value[0] = m[0];
        value[1] = m[1];
        value[2] = m[2];
        return *this;
    }

    mat<3, 3, T> &operator+=(T s)
    {
        value[0] += s;
        value[1] += s;
        value[2] += s;
        return *this;
    }

    mat<3, 3, T> &operator+=(mat<3, 3, T> const &m)
    {
        value[0] += m[0];
        value[1] += m[1];
        value[2] += m[2];
        return *this;
    }

    mat<3, 3, T> &operator-=(T s)
    {
        value[0] -= s;
        value[1] -= s;
        value[2] -= s;
        return *this;
    }

    mat<3, 3, T> &operator-=(mat<3, 3, T> const &m)
    {
        value[0] -= m[0];
        value[1] -= m[1];
        value[2] -= m[2];
        return *this;
    }

    mat<3, 3, T> &operator*=(T s)
    {
        value[0] *= s;
        value[1] *= s;
        value[2] *= s;
        return *this;
    }

    mat<3, 3, T> &operator*=(mat<3, 3, T> const &m)
    {
        typename mat<3, 3, T>::col_type const &a0 = value[0];
        typename mat<3, 3, T>::col_type const &a1 = value[1];
        typename mat<3, 3, T>::col_type const &a2 = value[2];
        typename mat<3, 3, T>::col_type const &b0 = m[0];
        typename mat<3, 3, T>::col_type const &b1 = m[1];
        typename mat<3, 3, T>::col_type const &b2 = m[2];

        typename mat<3, 3, T>::col_type tmp0 = a0 * b0.x;
        tmp0 += a1 * b0.y;
        tmp0 += a2 * b0.z;

        typename mat<3, 3, T>::col_type tmp1 = a0 * b1.x;
        tmp1 += a1 * b1.y;
        tmp1 += a2 * b1.z;

        typename mat<3, 3, T>::col_type tmp2 = a0 * b2.x;
        tmp2 += a1 * b2.y;
        tmp2 += a2 * b2.z;

        value[0] = tmp0;
        value[1] = tmp1;
        value[2] = tmp2;

        return *this;
    }

    col_type &operator[](size_t index)
    {
        return value[index];
    }

    col_type const &operator[](size_t index) const
    {
        return value[index];
    }

    bool operator==(mat<3, 3, T> const &other) const
    {
        return value[0] == other[0] && value[1] == other[1] && value[2] == other[2];
    }

    bool operator!=(mat<3, 3, T> const &other) const
    {
        return value[0] != other[0] || value[1] != other[1] || value[2] != other[2];
    }
};

template <typename T>
mat<3, 3, T> operator+(mat<3, 3, T> const &m1, mat<3, 3, T> const &m2)
{
    mat<3, 3, T> result;
    result[0] = m1[0] + m2[0];
    result[1] = m1[1] + m2[1];
    result[2] = m1[2] + m2[2];
    return result;
}

template <typename T>
mat<3, 3, T> operator-(mat<3, 3, T> const &m1, mat<3, 3, T> const &m2)
{
    mat<3, 3, T> result;
    result[0] = m1[0] - m2[0];
    result[1] = m1[1] - m2[1];
    result[2] = m1[2] - m2[2];
    return result;
}

template <typename T>
mat<3, 3, T> operator*(mat<3, 3, T> const &m1, mat<3, 3, T> const &m2)
{
    // treats the columns of B as linear combinations of the columns
    // of A, performing column major order multiplication.
    //
    // in row major order, this is the result of BA instead of AB.

    typename mat<3, 3, T>::col_type const &a0 = m1[0];
    typename mat<3, 3, T>::col_type const &a1 = m1[1];
    typename mat<3, 3, T>::col_type const &a2 = m1[2];
    typename mat<3, 3, T>::col_type const &b0 = m2[0];
    typename mat<3, 3, T>::col_type const &b1 = m2[1];
    typename mat<3, 3, T>::col_type const &b2 = m2[2];

    typename mat<3, 3, T>::col_type tmp0 = a0 * b0.x;
    tmp0 += a1 * b0.y;
    tmp0 += a2 * b0.z;

    typename mat<3, 3, T>::col_type tmp1 = a0 * b1.x;
    tmp1 += a1 * b1.y;
    tmp1 += a2 * b1.z;

    typename mat<3, 3, T>::col_type tmp2 = a0 * b2.x;
    tmp2 += a1 * b2.y;
    tmp2 += a2 * b2.z;

    return mat<3, 3, T>(tmp0, tmp1, tmp2);
}

} // namespace engine