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

  private:
    std::array<Vector<N, T>, M> data;
};

typedef Matrix<4, 4, float> Mat4;
typedef Matrix<3, 3, float> Mat3;
typedef Matrix<2, 2, float> Mat2;

} // namespace engine