#pragma once

#include "type_vec2.hpp"

namespace engine
{

template <int M, int N, typename T>
struct mat;

template <typename T>
struct mat<2, 2, T>
{
    // clang-format off
    static constexpr size_t length() { return 2; }
    // clang-format on

    typedef vec<2, T> col_type;
    typedef vec<2, T> row_type;

  private:
    col_type value[2];

  public:
    mat() = default;

    mat(T scalar)
    {
        value[0] = col_type(scalar, T(0));
        value[1] = col_type(T(0), scalar);
    }

    // clang-format off
    mat(T const &x1, T const &y1,
        T const &x2, T const &y2)
    {
        value[0] = col_type(x1, y1);
        value[1] = col_type(x2, y2);
    }

    mat(col_type const &v1,
        col_type const &v2)
    {
        value[0] = v1;
        value[1] = v2;
    }
    // clang-format on

    mat<2, 2, T> &operator=(mat<2, 2, T> const &m)
    {
        value[0] = m[0];
        value[1] = m[1];
        return *this;
    }

    mat<2, 2, T> &operator+=(T s)
    {
        value[0] += s;
        value[1] += s;
        return *this;
    }

    mat<2, 2, T> &operator+=(mat<2, 2, T> const &m)
    {
        value[0] += m[0];
        value[1] += m[1];
        return *this;
    }

    mat<2, 2, T> &operator-=(T s)
    {
        value[0] -= s;
        value[1] -= s;
        return *this;
    }

    mat<2, 2, T> &operator-=(mat<2, 2, T> const &m)
    {
        value[0] -= m[0];
        value[1] -= m[1];
        return *this;
    }

    mat<2, 2, T> &operator*=(T s)
    {
        value[0] *= s;
        value[1] *= s;
        return *this;
    }

    mat<2, 2, T> &operator*=(mat<2, 2, T> const &m)
    {
        typename mat<2, 2, T>::col_type const &a0 = value[0];
        typename mat<2, 2, T>::col_type const &a1 = value[1];
        typename mat<2, 2, T>::col_type const &b0 = m[0];
        typename mat<2, 2, T>::col_type const &b1 = m[1];

        typename mat<2, 2, T>::col_type tmp0 = a0 * b0.x;
        tmp0 += a1 * b0.y;

        typename mat<2, 2, T>::col_type tmp1 = a0 * b1.x;
        tmp1 += a1 * b1.y;

        value[0] = tmp0;
        value[1] = tmp1;

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

    bool operator==(mat<2, 2, T> const &other) const
    {
        return value[0] == other[0] && value[1] == other[1];
    }

    bool operator!=(mat<2, 2, T> const &other) const
    {
        return value[0] != other[0] || value[1] != other[1];
    }
};

template <typename T>
mat<2, 2, T> operator+(mat<2, 2, T> const &m1, mat<2, 2, T> const &m2)
{
    mat<2, 2, T> result;
    result[0] = m1[0] + m2[0];
    result[1] = m1[1] + m2[1];
    return result;
}

template <typename T>
mat<2, 2, T> operator-(mat<2, 2, T> const &m1, mat<2, 2, T> const &m2)
{
    mat<2, 2, T> result;
    result[0] = m1[0] - m2[0];
    result[1] = m1[1] - m2[1];
    return result;
}

template <typename T>
mat<2, 2, T> operator*(mat<2, 2, T> const &m1, mat<2, 2, T> const &m2)
{
    // treats the columns of B as linear combinations of the columns
    // of A, performing column major order multiplication.
    //
    // in row major order, this is the result of BA instead of AB.

    typename mat<2, 2, T>::col_type const &a0 = m1[0];
    typename mat<2, 2, T>::col_type const &a1 = m1[1];
    typename mat<2, 2, T>::col_type const &b0 = m2[0];
    typename mat<2, 2, T>::col_type const &b1 = m2[1];

    typename mat<2, 2, T>::col_type tmp0 = a0 * b0.x;
    tmp0 += a1 * b0.y;

    typename mat<2, 2, T>::col_type tmp1 = a0 * b1.x;
    tmp1 += a1 * b1.y;

    return mat<2, 2, T>(tmp0, tmp1);
}

template <typename T>
vec<2, T> operator*(const mat<2, 2, T> &m, vec<2, T> const &v)
{
    // treats the columns of B as linear combinations of the columns
    // of A, performing column major order multiplication.
    //
    // in row major order, this is the result of BA instead of AB.

    typename mat<2, 2, T>::col_type const &a0   = m[0];
    typename mat<2, 2, T>::col_type const &a1   = m[1];
    typename mat<2, 2, T>::col_type        tmp0 = a0 * v.x;
    tmp0 += a1 * v.y;

    return tmp0;
}

} // namespace engine
