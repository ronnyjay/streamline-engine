#include "core/application.hpp"

#include "math/matrix.hpp" // IWYU pragma: keep
#include "math/trig.hpp"   // IWYU pragma: keep
#include "math/vector.hpp" // IWYU pragma: keep

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

using namespace engine;

//

Application gApplication;

//

int main(void)
{

    float far    = 1000.0f;
    float near   = 0.1f;
    float aspect = 4.0f / 3.0f;
    float fov    = 45.0f;

    auto  res_a  = glm::perspective(glm::radians(fov), aspect, near, far);
    auto  res_b  = Perspective(math::ToRadians(fov), aspect, near, far);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", res_a[i][j]);
            if (j == 3)
                printf("\n");
        }
    }

    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", res_b[i][j]);
            if (j == 3)
                printf("\n");
        }
    }

    gApplication.Run();

    return 0;
}