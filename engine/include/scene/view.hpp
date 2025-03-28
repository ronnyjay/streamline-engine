#pragma once

#include "assert.hpp"
#include "pool.hpp"

namespace engine
{

template <typename T>
class basic_view
{
    const component_storage<T> &storage;

  public:
    using iterator       = typename std::vector<std::uint32_t>::const_iterator;
    using const_iterator = typename std::vector<std::uint32_t>::const_iterator;

    // clang-format off
    iterator       begin()       { return storage.begin(); }
    const_iterator begin() const { return storage.begin(); }
    iterator       end()         { return storage.begin() + storage.size(); }
    const_iterator end()   const { return storage.begin() + storage.size(); }
    // clang-format on

    explicit basic_view(const component_storage<T> &storage)
        : storage(storage)
    {
    }

    T &get(const std::uint32_t entity)
    {
        return (const_cast<component_storage<T> &>(storage)).get(entity);
    }
};

template <typename... Ts>
class multi_view
{
    component_storage_pool &storage;

    const sparse_set        entities;

  public:
    using iterator       = typename std::vector<std::uint32_t>::const_iterator;
    using const_iterator = typename std::vector<std::uint32_t>::const_iterator;

    // clang-format off
    iterator       begin()       { return entities.begin(); }
    const_iterator begin() const { return entities.begin(); }
    iterator       end()         { return entities.begin() + entities.size(); }
    const_iterator end()   const { return entities.begin() + entities.size(); }
    // clang-format on

    template <typename T>
    T &get(const std::uint32_t entity)
    {
        return storage.get<T>()->get(entity);
    }

    explicit multi_view(component_storage_pool &storage)
        : storage(storage)
    {
        STREAMLINE_ASSERT(sizeof...(Ts) > 0);

        // extract the first component array
        const_cast<sparse_set &>(entities) =
            static_cast<sparse_set &>(*(storage.get<std::tuple_element_t<0, std::tuple<Ts...>>>()));

        // perform an intersection on all following sets
        ((const_cast<sparse_set &>(entities) =
              const_cast<sparse_set &>(entities).intersect(static_cast<sparse_set &>(*storage.get<Ts>()))),
         ...);
    }

    std::tuple<Ts &...> get(const std::uint32_t entity)
    {
        return std::tuple<Ts &...>{storage.get<Ts>()->get(entity)...};
    }

    size_t size() const
    {
        return entities.size();
    }
};

} // namespace engine