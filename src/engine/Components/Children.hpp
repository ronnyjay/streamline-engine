#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace engine
{

struct Children
{
    Children() = default;
    Children(const Children &) = default;

    std::vector<entt::entity> children;
};

}; // namespace engine