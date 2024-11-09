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

    // clang-format off
    glm::mat4 matrix_a = glm::mat4(
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f
    );
    // clang-format on

    glm::mat4 result = matrix * matrix_a;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", result[i][j]);
            if (j == 3)
                printf("\n");
        }
    }
    printf("\n");

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        result = matrix * matrix_a;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "glm multiplication took: " << duration.count() << " ms." << std::endl << std::endl;
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

    // clang-format off
    Matrix<4, 4, float> matrix_b = slm::mat4(
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f
    );
    // clang-format on

    slm::mat4 result = matrix * matrix_b;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", result[i][j]);
            if (j == 3)
                printf("\n");
        }
    }
    printf("\n");

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        result = matrix * matrix_b;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "slm multiplication took: " << duration.count() << " ms." << std::endl;
}

int main(void)
{

    // glm::mat4 glm_rot = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 10.0f, 1.0f));
    // slm::mat4 slm_rot = slm::translate(slm::mat4(1.0f), slm::vec3(1.0f, 10.0f, 1.0f));
    // // glm::mat4 glm_rot(1.0f);
    // // slm::mat4 slm_rot(1.0f);

    // printf("%f\n%f\n", glm::radians(45.0f), slm::radians(45.0f));

    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%f ", glm_rot[i][j]);
    //         if (j == 3)
    //             printf("\n");
    //     }
    // }
    // printf("\n");

    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%f ", slm_rot[i][j]);
    //         if (j == 3)
    //             printf("\n");
    //     }
    // }
    // printf("\n");
}