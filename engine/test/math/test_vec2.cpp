#include "../../include/math/vec2.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(VEC2, TestEqualsAssignment)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2 = v1;

    EXPECT_EQ(v1.x, v2.x);
    EXPECT_EQ(v1.y, v2.y);
}

TEST(VEC2, TestAdditionAssignment)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 += v2;

    EXPECT_EQ(result.x, 4.0f);
    EXPECT_EQ(result.y, 6.0f);
}

TEST(VEC2, TestAddition)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 + v2;

    EXPECT_EQ(result.x, 4.0f);
    EXPECT_EQ(result.y, 6.0f);
}

TEST(VEC2, TestSubtractionAssignment)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 -= v2;

    EXPECT_EQ(result.x, -2.0f);
    EXPECT_EQ(result.y, -2.0f);
}

TEST(VEC2, TestSubtraction)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 - v2;

    EXPECT_EQ(result.x, -2.0f);
    EXPECT_EQ(result.y, -2.0f);
}

TEST(VEC2, TestMultiplicationAssignment)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 *= v2;

    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 8.0f);
}

TEST(VEC2, TestMultiplication)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 * v2;

    EXPECT_EQ(result.x, 3.0f);
    EXPECT_EQ(result.y, 8.0f);
}

TEST(VEC2, TestDivisionAssignment)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 /= v2;

    EXPECT_EQ(result.x, (1.0f / 3.0f));
    EXPECT_EQ(result.y, (1.0f / 2.0f));
}

TEST(VEC2, TestDivision)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    vec2 result = v1 / v2;

    EXPECT_EQ(result.x, (1.0f / 3.0f));
    EXPECT_EQ(result.y, (1.0f / 2.0f));
}

TEST(VEC2, TestOperatorEqualsWhenEqual)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(1.0f, 2.0f);

    EXPECT_EQ(v1 == v2, true);
}

TEST(VEC2, TestOperatorEqualsWhenNotEqual)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    EXPECT_EQ(v1 == v2, false);
}

TEST(VEC2, TestOperatorNotEqualsWhenEqual)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(1.0f, 2.0f);

    EXPECT_EQ(v1 != v2, false);
}

TEST(VEC2, TestOperatorNotEqualsWhenNotEqual)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    EXPECT_EQ(v1 != v2, true);
}
