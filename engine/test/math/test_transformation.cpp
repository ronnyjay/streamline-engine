#include "../include/math/transformation.hpp" // IWYU pragma: keep

#include "../include/math/mat4x4.hpp"         // IWYU pragma: keep
#include "../include/math/vec3.hpp"           // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(TRANSFORMATION, TestTranslate)
{
    // clang-format off
    vec3 v = vec3(1.0f, 2.0f, 3.0f);

    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );

    mat4 m2 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        10.0f, 11.0f, 10.0f, 11.0f
    );

    mat4 m3 = translate(m1, v);
    // clang-format on

    ASSERT_EQ(m2, m3);
}

TEST(TRANSFORMATION, TestRotate)
{
}

TEST(TRANSFORMATION, TestScale)
{
}

TEST(TRANSFORMATION, TestInverse)
{
}

TEST(TRANSFORMATION, TestTranspose)
{
}

TEST(TRANSFORMATION, TestPerspective)
{
}

TEST(TRANSFORMATION, TestOrthographic)
{
}
