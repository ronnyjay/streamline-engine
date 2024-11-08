#pragma once

#if defined(__AVX__) || defined(__FMA__)
#include <immintrin.h>
#endif

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

#if defined(__AVX__) || defined(__FMA__)

    // /**
    //  * @brief Standard matrix multiplication
    //  *
    //  * @return Matrix<M, P, T>
    //  */
    // template <
    //     std::size_t X = M, std::size_t Y = N, typename U = T,
    //     typename = std::enable_if_t<
    //         !((X == 4 && Y == 4 && std::is_same<U, float>::value) ||
    //           (X == 3 && Y == 3 && std::is_same<U, float>::value) ||
    //           (X == 2 && Y == 2 && std::is_same<U, float>::value))>,
    //     std::size_t P>
    // Matrix<M, P, T> operator*(const Matrix<N, P, T> &other) const
    // {
    // }

    /**
     * @brief SIMD multiplication for 4x4 matrices
     *
     * @param other
     * @return Matrix<4, 4, T>
     */
    template <typename U = T, std::enable_if_t<M == 4 && N == 4 && std::is_same<U, float>::value, int> = 0>
    Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &other) const
    {
        Matrix<4, 4, T> result;

        // clang-format off
        union { __m128 simd_vector; float  coefficients[4]; };

        __m128 simd_matrix_columns[4];
        simd_matrix_columns[0] = _mm_setr_ps(data[0][0], data[0][1], data[0][2], data[0][3]);
        simd_matrix_columns[1] = _mm_setr_ps(data[1][0], data[1][1], data[1][2], data[1][3]);
        simd_matrix_columns[2] = _mm_setr_ps(data[2][0], data[2][1], data[2][2], data[2][3]);
        simd_matrix_columns[3] = _mm_setr_ps(data[3][0], data[3][1], data[3][2], data[3][3]);

        for (size_t i = 0; i < 4; i++)
        {
            coefficients[0] = other[i][0];
            coefficients[1] = other[i][1];
            coefficients[2] = other[i][2];
            coefficients[3] = other[i][3];

            _mm_setr_ps( coefficients[0], coefficients[1], coefficients[2], coefficients[3]);

            __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
            _mm_fmadd_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1],
            _mm_fmadd_ps(_mm_set1_ps(coefficients[2]), simd_matrix_columns[2],
                    _mm_mul_ps(_mm_set1_ps(coefficients[3]), simd_matrix_columns[3])
                    )
                )
            );

            float simd_results[4];
            _mm_store_ps(simd_results, simd_result);

            result[i][0] = simd_results[0];
            result[i][1] = simd_results[1];
            result[i][2] = simd_results[2];
            result[i][3] = simd_results[3];
        }
        // clang-format on

        return result;
    }

#else

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

#endif

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

#if defined(__AVX__) || defined(__FMA__)
    // clang-format off

     /**
     * @brief
     *
     * @param other
     * @return Vector<M, T>
     */
    template <
        std::size_t X = M, std::size_t Y = N, typename U = T,
        typename = std::enable_if_t<
            !((X == 4 && Y == 4 && std::is_same<U, float>::value) ||
              (X == 3 && Y == 3 && std::is_same<U, float>::value) ||
              (X == 2 && Y == 2 && std::is_same<U, float>::value))>>
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

    template <typename = std::enable_if<M == 2 && N == 2>>
    Vector<2, T> operator*(const Vector<2, T> &other)
    {
        union { __m128 simd_vector; float  coefficients[2]; };

        coefficients[0] = other[0];
        coefficients[1] = other[1];

        _mm_setr_ps(0.0f, 0.0f, coefficients[0], coefficients[1]);

        __m128 simd_matrix_columns[2];
        simd_matrix_columns[0] = _mm_setr_ps(0.0f, 0.0f, data[0][0], data[0][1]);
        simd_matrix_columns[1] = _mm_setr_ps(0.0f, 0.0f, data[1][0], data[1][1]);

        __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
             _mm_mul_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1]));

        float simd_results[4];
        _mm_store_ps(simd_results, simd_result);

        return Vector<2, T>(simd_results[0], simd_results[1]);
    }

    template <typename = std::enable_if<M == 3 && N == 3>>
    Vector<3, T> operator*(const Vector<3, T> &other)
    {
        union { __m128 simd_vector; float  coefficients[3]; };
    }

    template <typename U = T, std::enable_if_t<M == 4 && N == 4 && std::is_same<U, float>::value, int> = 0>
    Vector<4, T> operator*(const Vector<4, T> &other)
    {
       union { __m128 simd_vector; float  coefficients[4]; };

        coefficients[0] = other[0];
        coefficients[1] = other[1];
        coefficients[2] = other[2];
        coefficients[3] = other[3];

        _mm_setr_ps( coefficients[0], coefficients[1], coefficients[2], coefficients[3]);

        __m128 simd_matrix_columns[4];
        simd_matrix_columns[0] = _mm_setr_ps(data[0][0], data[0][1], data[0][2], data[0][3]);
        simd_matrix_columns[1] = _mm_setr_ps(data[1][0], data[1][1], data[1][2], data[1][3]);
        simd_matrix_columns[2] = _mm_setr_ps(data[2][0], data[2][1], data[2][2], data[2][3]);
        simd_matrix_columns[3] = _mm_setr_ps(data[3][0], data[3][1], data[3][2], data[3][3]);

        __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
            _mm_fmadd_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1],
            _mm_fmadd_ps(_mm_set1_ps(coefficients[2]), simd_matrix_columns[2],
                    _mm_mul_ps(_mm_set1_ps(coefficients[3]), simd_matrix_columns[3])
                )
            )
        );

        float simd_results[4];
        _mm_store_ps(simd_results, simd_result);

        return Vector<4, T>(simd_results[0], simd_results[1], simd_results[2], simd_results[3]);
    }
    //clang-format on

#else

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

#endif

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