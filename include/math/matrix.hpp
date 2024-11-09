#pragma once

#if defined(__AVX__) || defined(__FMA__)
#include <immintrin.h>
#endif

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

    /**
     * @brief Performs naive multiplication between two MxN matrices
     *
     * @return Matrix<M, P, T>
     */
    template <
        std::size_t X = M, std::size_t Y = N, typename U = T,
        typename = std::enable_if_t<
            !((X == 4 && Y == 4 && std::is_same<U, float>::value) ||
              (X == 3 && Y == 3 && std::is_same<U, float>::value) ||
              (X == 2 && Y == 2 && std::is_same<U, float>::value))>,
        std::size_t P>
    Matrix<M, P, T> operator*(const Matrix<N, P, T> &other) const
    {
    }

    /**
     * @brief Perfoms naive multiplication between and MxN matrix and and N-component vector
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

    /**
     * @brief Performs SIMD-optimized multiplication between two 4x4 matrices
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

    /**
     * @brief Performs SIMD-optimized multiplication between two 3x3 matrices
     *
     * @tparam U
     * @param other
     * @return Matrix<3, 3, T>
     */
    template <typename U = T, std::enable_if_t<M == 3 && N == 3 && std::is_same<U, float>::value, int> = 0>
    Matrix<3, 3, T> operator*(const Matrix<3, 3, T> &other) const
    {
        Matrix<3, 3, T> result;

        // clang-format off
        union { __m128 simd_vector; float  coefficients[3]; };

        __m128 simd_matrix_columns[3];
        simd_matrix_columns[0] = _mm_setr_ps(data[0][0], data[0][1], data[0][2], 0.0f);
        simd_matrix_columns[1] = _mm_setr_ps(data[1][0], data[1][1], data[1][2], 0.0f);
        simd_matrix_columns[2] = _mm_setr_ps(data[2][0], data[2][1], data[2][2], 0.0f);

        for (size_t i = 0; i <3; i++)
        {
            coefficients[0] = other[i][0];
            coefficients[1] = other[i][1];
            coefficients[2] = other[i][2];

            _mm_setr_ps(0.0f, coefficients[0], coefficients[1], coefficients[2]);

            __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
                _mm_fmadd_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1],
                    _mm_mul_ps(_mm_set1_ps(coefficients[2]), simd_matrix_columns[2]
                    )
                )
            );

            float simd_results[4];
            _mm_store_ps(simd_results, simd_result);

            result[i][0] = simd_results[0];
            result[i][1] = simd_results[1];
            result[i][2] = simd_results[2];
        }
        // clang-format on

        return result;
    }

    /**
     * @brief Performs SIMD-optimized multiplication between two 2x2 matrices
     *
     * @tparam U
     * @param other
     * @return Matrix<2, 2, T>
     */
    template <typename U = T, std::enable_if_t<M == 2 && N == 2 && std::is_same<U, float>::value, int> = 0>
    Matrix<2, 2, T> operator*(const Matrix<2, 2, T> &other) const
    {
        Matrix<2, 2, T> result;

        // clang-format off
        union { __m128 simd_vector; float  coefficients[2]; };

        __m128 simd_matrix_columns[2];
        simd_matrix_columns[0] = _mm_setr_ps(data[0][0], data[0][1], 0.0f, 0.0f);
        simd_matrix_columns[1] = _mm_setr_ps(data[1][0], data[1][1], 0.0f, 0.0f);

        for (size_t i = 0; i < 2; i++)
        {
            coefficients[0] = other[i][0];
            coefficients[1] = other[i][1];

            _mm_setr_ps(0.0f, 0.0f, coefficients[0], coefficients[1]);

            __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
                _mm_mul_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1]
                )
            );

            float simd_results[4];
            _mm_store_ps(simd_results, simd_result);

            result[i][0] = simd_results[0];
            result[i][1] = simd_results[1];
        }
        // clang-format on

        return result;
    }

    /**
     * @brief Performs SIMD-optimized multiplication between a 4x4 matrix and a 4-component vector
     *
     * @tparam U
     * @param other
     * @return Vector<4, T>
     */
    template <typename U = T, std::enable_if_t<M == 4 && N == 4 && std::is_same<U, float>::value, int> = 0>
    Vector<4, T> operator*(const Vector<4, T> &other)
    {
        // clang-format off
        union { __m128 simd_vector; float  coefficients[4]; };

        coefficients[0] = other[0];
        coefficients[1] = other[1];
        coefficients[2] = other[2];
        coefficients[3] = other[3];

        _mm_setr_ps(coefficients[0], coefficients[1], coefficients[2], coefficients[3]);

        __m128 simd_matrix_columns[4];
        simd_matrix_columns[0] = _mm_setr_ps(data[0][0], data[0][1], data[0][2], data[0][3]);
        simd_matrix_columns[1] = _mm_setr_ps(data[1][0], data[1][1], data[1][2], data[1][3]);
        simd_matrix_columns[2] = _mm_setr_ps(data[2][0], data[2][1], data[2][2], data[2][3]);
        simd_matrix_columns[3] = _mm_setr_ps(data[3][0], data[3][1], data[3][2], data[3][3]);

        __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
            _mm_fmadd_ps(_mm_set1_ps(coefficients[1]),simd_matrix_columns[1],
                _mm_fmadd_ps( _mm_set1_ps(coefficients[2]), simd_matrix_columns[2],
                    _mm_mul_ps(_mm_set1_ps(coefficients[3]), simd_matrix_columns[3])
                )
            )
        );
        // clang-format on

        float simd_results[4];
        _mm_store_ps(simd_results, simd_result);

        return Vector<4, T>(simd_results[0], simd_results[1], simd_results[2], simd_results[3]);
    }

#else

    /**
     * @brief Performs naive multiplication between two MxN matrices
     *
     * @tparam P
     * @param other
     * @return Matrix<M, P, T>
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
     * @brief Performs naive multiplication between an MxN matrix and a N-component vector
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

#endif

    /**
     * @brief Performs scalar multiplication on an MxN matrix
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
inline Matrix<4, 4, T> translate(const Matrix<4, 4, T> &m, const Vector<3, T> &v)
{
    Matrix<4, 4, T> translation(1.0f);
    translation[3][0] = v.x;
    translation[3][1] = v.y;
    translation[3][2] = v.z;
    translation[3][3] = 1.0f;

    return m * translation;
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