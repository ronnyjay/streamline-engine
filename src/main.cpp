#include "core/application.hpp"

#include "math/fwd.hpp"    // IWYU pragma: keep
#include "math/matrix.hpp" // IWYU pragma: keep
#include "math/trig.hpp"   // IWYU pragma: keep
#include "math/vector.hpp" // IWYU pragma: keep

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

#include <immintrin.h>

#include <chrono>

using namespace engine;

//

Application gApplication;

//

void benchmark_glm()
{
    glm::vec4 vector = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);

    // clang-format off
    glm::mat4 matrix = glm::mat4(
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f
    );
    // clang-format on

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        glm::vec4 result = matrix * vector;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "glm multiplication took: " << duration.count() << " ms." << std::endl;
}

void benchmark_slm()
{
    Vector<4, float> vector = slm::vec4(1.0f, 2.0f, 3.0f, 4.0f);

    // clang-format off
    Matrix<4, 4, float> matrix = slm::mat4(
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f
    );
    // clang-format on

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        slm::vec4 result = matrix * vector;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "slm multiplication took: " << duration.count() << " ms." << std::endl;
}

// void benchmark_slm()
// {
//     // clang-format off
//     union { __m128 simd_vector; float coefficients[4]; };
//     // clang-format on

//     slm::vec4 vector = slm::vec4(1.0f, 2.0f, 3.0f, 4.0f);

//     // clang-format off
//     slm::mat4 matrix = slm::mat4(
//         1.0f, 5.0f, 9.0f, 13.0f,
//         2.0f, 6.0f, 10.0f, 14.0f,
//         3.0f, 7.0f, 11.0f, 15.0f,
//         4.0f, 8.0f, 12.0f, 16.0f
//     );
//     // clang-format on

//     coefficients[0] = vector.x;
//     coefficients[1] = vector.y;
//     coefficients[2] = vector.z;
//     coefficients[3] = vector.w;

//     _mm_setr_ps(vector.x, vector.y, vector.z, vector.w);

//     __m128 simd_matrix_columns[4];
//     simd_matrix_columns[0] = _mm_setr_ps(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
//     simd_matrix_columns[1] = _mm_setr_ps(matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
//     simd_matrix_columns[2] = _mm_setr_ps(matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
//     simd_matrix_columns[3] = _mm_setr_ps(matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);

//     auto start = std::chrono::high_resolution_clock::now();
//     for (int i = 0; i < 1000000; i++)
//     {

//         // clang-format off
//         __m128 simd_result = _mm_fmadd_ps(_mm_set1_ps(coefficients[0]), simd_matrix_columns[0],
//             _mm_fmadd_ps(_mm_set1_ps(coefficients[1]), simd_matrix_columns[1],
//             _mm_fmadd_ps(_mm_set1_ps(coefficients[2]), simd_matrix_columns[2],
//                     _mm_mul_ps(_mm_set1_ps(coefficients[3]), simd_matrix_columns[3])
//                 )
//             )
//         );
//         // clang-format on
//     }
//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//     std::cout << "slm multiplication took: " << duration.count() << " ms." << std::endl;
// }

int main(void)
{
    benchmark_glm();
    benchmark_slm();
}