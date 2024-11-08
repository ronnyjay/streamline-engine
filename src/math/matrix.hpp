#pragma once

#include <xmmintrin.h> // SSE intrinsics

#include "vector.hpp"

namespace engine
{

template <std::size_t M, std::size_t N, typename T>
class Matrix
{
  public:
    /**
     * @brief
     *
     */
    Matrix() = default;

    /**
     * @brief
     *
     * @param s
     */
    Matrix(T s)
    {
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                if (i == j)
                    data[i][j] = s;
            }
        }
    }

    template <typename... Args, typename = std::enable_if<sizeof...(Args) == M * N>>
    Matrix(Args... args)
    {
        T values[] = {args...};
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                data[i][j] = values[i * N + j];
            }
        }
    }

    /**
     * @brief
     *
     * @param i
     * @return Vector<N, T>&
     */
    Vector<N, T> &operator[](std::size_t i)
    {
        return data[i];
    }

    /**
     * @brief
     *
     * @param i
     * @return Vector<N, T>&
     */
    const Vector<N, T> &operator[](std::size_t i) const
    {
        return data[i];
    }

    /**
     * @brief
     *
     * @param other
     * @return Matrix<M, N, T>
     */
    Matrix<M, N, T> operator+(const Matrix<M, N, T> &other) const
    {
        Matrix<M, N, T> matrix;

        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                matrix[i][j] = data[i][j] + other[i][j];
            }
        }

        return matrix;
    }

    /**
     * @brief
     *
     * @param other
     * @return Matrix<M, N, T>
     */
    Matrix<M, N, T> operator-(const Matrix<M, N, T> &other) const
    {
        Matrix<M, N, T> m;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                m[i][j] = data[i][j] - other[i][j];
            }
        }
        return m;
    }

    /**
     * @brief
     *
     * @tparam P
     * @param other
     * @return Matrix<N, N, T>
     */
    template <std::size_t P>
    Matrix<M, P, T> operator*(const Matrix<N, P, T> &other) const
    {
        Matrix<M, P, T> m;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < P; j++)
            {
                for (size_t k = 0; k < N; k++)
                {
                    m[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return m;
    }

    /**
     * @brief
     *
     * @param s
     * @return Matrix<M, N, T>
     */
    Matrix<M, N, T> operator*(T s) const
    {
        Matrix<M, N, T> m;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                m[i][j] = data[i][j] * s;
            }
        }
        return m;
    }

    /**
     * @brief
     *
     * @param other
     * @return Vector<M, T>
     */
    Vector<M, T> operator*(const Vector<N, T> &other)
    {
        Vector<M, T> v;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                v[i] += data[i][j] * other[j];
            }
        }
        return v;
    }

  private:
    std::array<Vector<N, T>, M> data;
}; // namespace engine

typedef Matrix<4, 4, float> Mat4;
typedef Matrix<3, 3, float> Mat3;
typedef Matrix<2, 2, float> Mat2;

namespace slm
{
/**
 * @brief
 *
 * @tparam T
 * @param v
 * @return Matrix<4, 4, T>
 */
template <typename T = float>
inline Matrix<4, 4, T> translate(const Vector<3, T> &v)
{
}

/**
 * @brief
 *
 * @tparam T
 * @param m
 * @return Matrix<4, 4, T>
 */
template <typename T = float>
inline Matrix<4, 4, T> inverse(const Matrix<4, 4, T> &m)
{
}

/**
 * @brief
 *
 * @tparam T
 * @param m
 * @param angle
 * @param axis
 * @return Matrix<4, 4, T>
 */
template <typename T = float>
inline Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &m, T angle, const Vector<3, T> &axis)
{
}

/**
 * @brief
 *
 * @tparam T
 * @param fov
 * @param aspectratio
 * @param near
 * @param far
 * @return Matrix<4, 4, T>
 */
template <typename T = float>
inline Matrix<4, 4, T> perspective(float fov, float aspect, float near, float far)
{
    Matrix<4, 4, T> proj;

    proj[0][0] = 1 / (aspect * tan(fov / 2));
    proj[1][1] = 1 / tan(fov / 2);
    proj[2][2] = -((far + near) / (far - near));
    proj[3][2] = -((2 * far * near) / (far - near));
    proj[2][3] = -1;

    return proj;
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @param top
 * @param bottom
 * @param near
 * @param far
 * @return Matrix<4, 4, T>
 */
template <typename T = float>
inline Matrix<4, 4, T> orthographic(float left, float right, float top, float bottom, float near, float far)
{
    Matrix<4, 4, T> proj;

    proj[0][0] = 2 / (right - left);
    proj[0][3] = -((right + left) / (right - left));
    proj[1][1] = 2 / (top - bottom);
    proj[1][3] = -((top + bottom) / (top - bottom));
    proj[2][2] = -(2 / (far - near));
    proj[2][3] = -((far + near) / (far - near));
    proj[3][3] = 1;

    return proj;
}

} // namespace slm

} // namespace engine