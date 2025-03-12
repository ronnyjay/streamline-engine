#include "../../include/math/mat4x4.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(MAT4x4, TestEqualsAssignment)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );

    mat4 m2 = m1;
    // clang-format on

    ASSERT_EQ(m1, m2);
}

TEST(MAT4x4, TestAdditionAssignment)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        3.0f, 3.0f, 3.0f, 3.0f, 
        3.0f, 3.0f, 3.0f, 3.0f,
        3.0f, 3.0f, 3.0f, 3.0f, 
        3.0f, 3.0f, 3.0f, 3.0f
    );

    mat4 m4 = m1 += m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT4x4, TestAddition)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        3.0f, 3.0f, 3.0f, 3.0f, 
        3.0f, 3.0f, 3.0f, 3.0f,
        3.0f, 3.0f, 3.0f, 3.0f, 
        3.0f, 3.0f, 3.0f, 3.0f
    );

    mat4 m4 = m1 += m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT4x4, TestSubstractionAssignment)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        -1.0f, 1.0f, -1.0f, 1.0f, 
        1.0f, -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 
        1.0f, -1.0f, 1.0f, -1.0f
    );

    mat4 m4 = m1 -= m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT4x4, TestSubstraction)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        -1.0f, 1.0f, -1.0f, 1.0f, 
        1.0f, -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 
        1.0f, -1.0f, 1.0f, -1.0f
    );

    mat4 m4 = m1 - m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT4x4, TestMultiplicationAssignment)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        8.0f, 10.0f, 8.0f, 10.0f, 
        10.0f, 8.0f, 10.0f, 8.0f,
        8.0f, 10.0f, 8.0f, 10.0f, 
        10.0f, 8.0f, 10.0f, 8.0f
    );

    mat4 m4 = m1 *= m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT4x4, TestMultiplication)
{
    // clang-format off
    mat4 m1 = mat4(
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f
    );
    mat4 m2 = mat4(
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f, 
        2.0f, 1.0f, 2.0f, 1.0f, 
        1.0f, 2.0f, 1.0f, 2.0f
    );
    mat4 m3=mat4(
        8.0f, 10.0f, 8.0f, 10.0f, 
        10.0f, 8.0f, 10.0f, 8.0f,
        8.0f, 10.0f, 8.0f, 10.0f, 
        10.0f, 8.0f, 10.0f, 8.0f
    );

    mat4 m4 = m1 * m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}
