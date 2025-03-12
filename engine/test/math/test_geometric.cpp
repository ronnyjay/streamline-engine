#include "../include/math/geometric.hpp" // IWYU pragma: keep

#include "../include/math/vec2.hpp"      // IWYU pragma: keep
#include "../include/math/vec3.hpp"      // IWYU pragma: keep
#include "../include/math/vec4.hpp"      // IWYU pragma: keep

#include <gtest/gtest.h>

using namespace engine;

TEST(GEOMETRIC, TestDotProduct2Members)
{
    vec2 v1(1.0f, 2.0f);
    vec2 v2(3.0f, 4.0f);

    ASSERT_EQ(dot(v1, v2), 11.0f);
}

TEST(GEOMETRIC, TestDotProduct3Members)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(dot(v1, v2), 32.0f);
}

TEST(GEOMETRIC, TestDotProduct4Members)
{
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

    ASSERT_EQ(dot(v1, v2), 70.0f);
}

TEST(GEOMETRIC, TestCrossProduct3Members)
{
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(cross(v1, v2), vec3(-3.0f, 6.0f, -3.0f));
}

TEST(GEOMETRIC, TestNormalize2Members)
{
    vec2 v(1.0f, 2.0f);

    EXPECT_NEAR(normalize(v).x, (1.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).y, (2.0f / length(v)), 1e-5f);
}

TEST(GEOMETRIC, TestNormalize3Members)
{
    vec3 v(1.0f, 2.0f, 3.0f);

    EXPECT_NEAR(normalize(v).x, (1.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).y, (2.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).z, (3.0f / length(v)), 1e-5f);
}

TEST(GEOMETRIC, TestNormalize4Members)
{
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_NEAR(normalize(v).x, (1.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).y, (2.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).z, (3.0f / length(v)), 1e-5f);
    EXPECT_NEAR(normalize(v).w, (4.0f / length(v)), 1e-5f);
}

TEST(GEOMETRIC, TestLength2Members)
{
    ASSERT_EQ(length(vec2(1.0f, 2.0f)), std::sqrt(5.0f));
}

TEST(GEOMETRIC, TestLength3Members)
{
    ASSERT_EQ(length(vec3(1.0f, 2.0f, 3.0f)), std::sqrt(14.0f));
}

TEST(GEOMETRIC, TestLength4Members)
{
    ASSERT_EQ(length(vec4(1.0f, 2.0f, 3.0f, 4.0f)), std::sqrt(30.0f));
}