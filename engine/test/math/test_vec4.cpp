#include "../../include/math/vec4.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(VEC4, TestEqualsAssignment)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2 = v1;

    EXPECT_EQ(v1.x, v2.x);
    EXPECT_EQ(v1.y, v2.y);
    EXPECT_EQ(v1.z, v2.z);
    EXPECT_EQ(v1.w, v2.w);
}

TEST(VEC4, TestAdditionAssignment)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 += v2;

    EXPECT_EQ(result.x, 6.0f);
    EXPECT_EQ(result.y, 8.0f);
    EXPECT_EQ(result.z, 10.0f);
    EXPECT_EQ(result.w, 12.0f);
}

TEST(VEC4, TestAddition)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 + v2;

    EXPECT_EQ(result.x, 6.0f);
    EXPECT_EQ(result.y, 8.0f);
    EXPECT_EQ(result.z, 10.0f);
    EXPECT_EQ(result.w, 12.0f);
}

TEST(VEC4, TestSubtractionAssignment)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 -= v2;

    EXPECT_EQ(result.x, -4.0f);
    EXPECT_EQ(result.y, -4.0f);
    EXPECT_EQ(result.z, -4.0f);
    EXPECT_EQ(result.w, -4.0f);
}

TEST(VEC4, TestSubtraction)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 - v2;

    EXPECT_EQ(result.x, -4.0f);
    EXPECT_EQ(result.y, -4.0f);
    EXPECT_EQ(result.z, -4.0f);
    EXPECT_EQ(result.w, -4.0f);
}

TEST(VEC4, TestMultiplicatonAssignment)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 *= v2;

    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 12.0f);
    EXPECT_EQ(result.z, 21.0f);
    EXPECT_EQ(result.w, 32.0f);
}

TEST(VEC4, TestMultiplicaton)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 * v2;

    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 12.0f);
    EXPECT_EQ(result.z, 21.0f);
    EXPECT_EQ(result.w, 32.0f);
}

TEST(VEC4, TestDivisionAssignment)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 /= v2;

    EXPECT_EQ(result.x, (1.0f / 5.0f));
    EXPECT_EQ(result.y, (2.0f / 6.0f));
    EXPECT_EQ(result.z, (3.0f / 7.0f));
    EXPECT_EQ(result.w, (4.0f / 8.0f));
}

TEST(VEC4, TestDivision)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    vec4 result = v1 / v2;

    EXPECT_EQ(result.x, (1.0f / 5.0f));
    EXPECT_EQ(result.y, (2.0f / 6.0f));
    EXPECT_EQ(result.z, (3.0f / 7.0f));
    EXPECT_EQ(result.w, (4.0f / 8.0f));
}

TEST(VEC4, TestOperatorEqualsWhenEqual)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_EQ(v1 == v2, true);
}

TEST(VEC4, TestOperatorEqualsWhenNotEqual)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_EQ(v1 == v2, false);
}

TEST(VEC4, TestOperatorNotEqualsWhenEqual)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_EQ(v1 != v2, false);
}

TEST(VEC4, TestOperatorNotEqualsWhenNotEqual)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_EQ(v1 != v2, true);
}