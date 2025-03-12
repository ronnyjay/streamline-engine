#include "../../include/math/mat2x2.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(MAT2x2, TestEqualsAssignment)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f,
        2.0f, 1.0f
    );

    mat2 m2 = m1;
    // clang-format on

    ASSERT_EQ(m1, m2);
}

TEST(MAT2x2, TestAdditionAssignment)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        2.0f, 3.0f, 
        4.0f, 2.0f
    );
    
    mat2 m4 = m1 += m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}

TEST(MAT2x2, TestAddition)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        2.0f, 3.0f, 
        4.0f, 2.0f
    );
    
    mat2 m4 = m1 + m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}

TEST(MAT2x2, TestSubstractionAssignment)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        0.0f, 1.0f, 
        0.0f, 0.0f
    );
    
    mat2 m4 = m1 -= m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}

TEST(MAT2x2, TestSubstraction)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        0.0f, 1.0f, 
        0.0f, 0.0f
    );
    
    mat2 m4 = m1 - m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}

TEST(MAT2x2, TestMultiplicationAssignment)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        3.0f, 3.0f, 
        4.0f, 5.0f
    );
    
    mat2 m4 = m1 *= m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}

TEST(MAT2x2, TestMultiplication)
{
    // clang-format off
    mat2 m1 = mat2(
        1.0f, 2.0f, 
        2.0f, 1.0f
    );
    mat2 m2 = mat2(
        1.0f, 1.0f, 
        2.0f, 1.0f
    );
    mat2 m3 = mat2(
        3.0f, 3.0f, 
        4.0f, 5.0f
    );
    
    mat2 m4 = m1 * m2;
    // clang-format on

    ASSERT_EQ(m3, m4);
}
