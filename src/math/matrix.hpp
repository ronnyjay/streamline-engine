#pragma once

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
};

typedef Matrix<4, 4, float> Mat4;
typedef Matrix<3, 3, float> Mat3;
typedef Matrix<2, 2, float> Mat2;

} // namespace engine