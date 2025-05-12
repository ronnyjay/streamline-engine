#include "scene/sparse_set.hpp"

#include <gtest/gtest.h>

using namespace engine;

TEST(SPARSE_SET, TestEmplace)
{
    // entity id
    const auto entity = 1;

    // index in packed
    const auto index = 0;

    SSet       set;
    set.emplace(entity);

    ASSERT_EQ(set.size(), 1);
    ASSERT_EQ(set.search(1), 0);
}

TEST(SPARSE_SET, TestRemove)
{
    // entity id's
    const uint32_t e1 = 1;
    const uint32_t e2 = 2;
    const uint32_t e3 = 3;

    // indices in packed
    const size_t i1 = 0;
    const size_t i3 = 1;

    SSet         set;
    set.emplace(e1);
    set.emplace(e2);
    set.emplace(e3);
    set.remove(e2);

    ASSERT_EQ(set.size(), 2);

    ASSERT_EQ(set.search(e1), i1);
    ASSERT_EQ(set.search(e3), i3);
}

TEST(SPARSE_SET, TestMaxEmplace)
{
    const auto e = SSet::null;

    SSet       set;
    set.emplace(e);

    ASSERT_EQ(set.size(), 0);
}
