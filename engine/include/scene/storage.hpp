#pragma once

#include "sparse_set.hpp"

namespace engine
{
template <typename T>
class ComponentStorage : public SSet
{
    std::vector<T> components;

  public:
    T &get(uint32_t const entity)
    {
        const auto index = search(entity);
        return components[index];
    }

    template <typename... Args>
    T &emplace(uint32_t const entity, auto &&...args)
    {
        SSet::emplace(entity);

        // clang-format off
        auto &elem 
            = components.emplace_back(
                std::forward<decltype(args)>(args)...);
        // clang-format on

        return elem;
    }

    void remove(uint32_t const entity)
    {
        const auto index = sparse[entity];
        const auto last  = size() - 1;

        SSet::remove(entity);

        components[index] = std::move(components[last]);
        components.pop_back();
    }
};
} // namespace engine