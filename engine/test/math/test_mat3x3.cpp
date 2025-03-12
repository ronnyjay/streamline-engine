#include "../../include/math/mat3x3.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(MAT3x3, TestEqualsAssignment)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );

    mat3 m2 = m1;
    // clang-format on

    ASSERT_EQ(m1, m2);
}

TEST(MAT3x3, TestAdditionAssignment)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        2.0f, 3.0f, 2.0f, 
        4.0f, 2.0f, 4.0f, 
        2.0f, 3.0f, 2.0f
    );

    mat3 m4 = m1 += m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT3x3, TestAddition)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        2.0f, 3.0f, 2.0f, 
        4.0f, 2.0f, 4.0f, 
        2.0f, 3.0f, 2.0f
    );

    mat3 m4 = m1 + m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT3x3, TestSubstractionAssignment)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, -1.0f, 0.0f
    );

    mat3 m4 = m1 -= m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT3x3, TestSubstraction)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, -1.0f, 0.0f
    );

    mat3 m4 = m1 - m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT3x3, TestMultiplicationAssignment)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        4.0f, 4.0f, 4.0f, 
        6.0f, 7.0f, 6.0f, 
        6.0f, 5.0f, 6.0f
    );

    mat3 m4 = m1 *= m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}

TEST(MAT3x3, TestMultiplication)
{
    // clang-format off
    mat3 m1 = mat3(
        1.0f, 2.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 1.0f, 1.0f
    );
    mat3 m2 = mat3(
        1.0f, 1.0f, 1.0f, 
        2.0f, 1.0f, 2.0f, 
        1.0f, 2.0f, 1.0f
    );
    mat3 m3 = mat3(
        4.0f, 4.0f, 4.0f, 
        6.0f, 7.0f, 6.0f, 
        6.0f, 5.0f, 6.0f
    );

    mat3 m4 = m1 * m2;
    // clang-format on

    EXPECT_EQ(m3, m4);
}
