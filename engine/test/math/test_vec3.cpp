#include "../../include/math/vec3.hpp" // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(VEC3, TestEqualsAssignment)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2 = v1;

    EXPECT_EQ(v1.x, v2.x);
    EXPECT_EQ(v1.y, v2.y);
    EXPECT_EQ(v1.z, v2.z);
}

TEST(VEC3, TestAdditionAssignment)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 += v2;

    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 7.0f);
    EXPECT_EQ(result.z, 9.0f);
}

TEST(VEC3, TestAddition)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 + v2;

    EXPECT_EQ(result.x, 5.0f);
    EXPECT_EQ(result.y, 7.0f);
    EXPECT_EQ(result.z, 9.0f);
}

TEST(VEC3, TestSubtractionAssignment)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 -= v2;

    EXPECT_EQ(result.x, -3.0f);
    EXPECT_EQ(result.y, -3.0f);
    EXPECT_EQ(result.z, -3.0f);
}

TEST(VEC3, TestSubtraction)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 - v2;

    EXPECT_EQ(result.x, -3.0f);
    EXPECT_EQ(result.y, -3.0f);
    EXPECT_EQ(result.z, -3.0f);
}

TEST(VEC3, TestMultiplicatonAssignment)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 *= v2;

    EXPECT_EQ(result.x, 4.0f);
    EXPECT_EQ(result.y, 10.0f);
    EXPECT_EQ(result.z, 18.0f);
}

TEST(VEC3, TestMultiplicaton)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 * v2;

    EXPECT_EQ(result.x, 4.0f);
    EXPECT_EQ(result.y, 10.0f);
    EXPECT_EQ(result.z, 18.0f);
}

TEST(VEC3, TestDivisionAssignment)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 /= v2;

    EXPECT_EQ(result.x, (1.0f / 4.0f));
    EXPECT_EQ(result.y, (2.0f / 5.0f));
    EXPECT_EQ(result.z, (3.0f / 6.0f));
}

TEST(VEC3, TestDivision)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    vec3 result = v1 / v2;

    EXPECT_EQ(result.x, (1.0f / 4.0f));
    EXPECT_EQ(result.y, (2.0f / 5.0f));
    EXPECT_EQ(result.z, (3.0f / 6.0f));
}

TEST(VEC3, TestOperatorEqualsWhenEqual)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(1.0f, 2.0f, 3.0f);

    EXPECT_EQ(v1 == v2, true);
}

TEST(VEC3, TestOperatorEqualsWhenNotEqual)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    EXPECT_EQ(v1 == v2, false);
}

TEST(VEC3, TestOperatorNotEqualsWhenEqual)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(1.0f, 2.0f, 3.0f);

    EXPECT_EQ(v1 != v2, false);
}

TEST(VEC3, TestOperatorNotEqualsWhenNotEqual)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    EXPECT_EQ(v1 != v2, true);
}