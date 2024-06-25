#pragma once

#include <entt/entt.hpp>

namespace engine
{

struct Parent
{
  public:
    Parent()
        : parent(entt::null)
    {
    }

    Parent(const Parent &) = default;

    entt::entity parent;
};

}; // namespace engine