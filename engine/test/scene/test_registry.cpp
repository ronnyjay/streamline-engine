#include "scene/entity.hpp"
#include "scene/registry.hpp"

#include <gtest/gtest.h>

using namespace engine;

struct test_component_a
{
    float dummy = 1.0f;
};

struct test_component_b
{
    float dummy = 1.0f;
};

struct test_component_c
{
    float dummy = 1.0f;
};

TEST(REGISTRY, TestDestroy)
{
    Registry    r;

    entity_type e1 = r.create();
    entity_type e2 = r.create();
    entity_type e3 = r.create();

    r.emplace<test_component_a>(e1);
    r.emplace<test_component_b>(e2);
    r.emplace<test_component_c>(e3);

    r.destroy(e1);
    r.destroy(e2);
    r.destroy(e3);

    ASSERT_EQ(r.all_of<test_component_a>(e1), false);
    ASSERT_EQ(r.all_of<test_component_b>(e2), false);
    ASSERT_EQ(r.all_of<test_component_c>(e3), false);
}

TEST(REGISTRY, TestAnyOf)
{
    Registry    r;

    entity_type e1 = r.create();
    r.emplace<test_component_a>(e1);
    r.emplace<test_component_b>(e1);

    ASSERT_EQ((r.any_of<test_component_c>(e1)), false);
    ASSERT_EQ((r.any_of<test_component_a, test_component_b, test_component_c>(e1)), true);
}

TEST(REGISTRY, TestAllOf)
{
    Registry    r;

    entity_type e1 = r.create();
    r.emplace<test_component_a>(e1);
    r.emplace<test_component_b>(e1);

    ASSERT_EQ((r.all_of<test_component_a, test_component_b>(e1)), true);
    ASSERT_EQ((r.all_of<test_component_a, test_component_b, test_component_c>(e1)), false);
}
