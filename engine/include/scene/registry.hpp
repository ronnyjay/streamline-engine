#pragma once

#include "pool.hpp"
#include "view.hpp"

namespace engine
{

class registry
{
    component_storage_pool pool;

    static uint32_t generate()
    {
        static uint32_t value = 0;
        return value++;
    }

  public:
    [[nodiscard]] auto create() const noexcept
    {
        const auto value = generate();
        return value;
    }

    void destroy(uint32_t const entity)
    {
        pool.remove(entity);
    }

    template <typename T, typename... Args>
    T &emplace(const std::uint32_t entity, Args &&...args)
    {
        return pool.get<T>()->emplace(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &get(const std::uint32_t entity)
    {
        return pool.get<T>()->get(entity);
    }

    template <typename T>
    T *try_get(const std::uint32_t entity)
    {
        component_storage<T> *storage = pool.get<T>();
        if (storage->search(entity) == sparse_set::null)
        {
            return nullptr;
        }
        return &storage->get(entity);
    }

    template <typename T>
    void remove(const std::uint32_t entity)
    {
        pool.get<T>()->remove(entity);
    }

    template <typename T>
    basic_view<T> view()
    {
        return basic_view<T>(*(pool.get<T>()));
    }

    template <typename... Ts, std::enable_if_t<(sizeof...(Ts) > 1), int> = 0>
    multi_view<Ts...> view()
    {
        return multi_view<Ts...>(pool);
    }

    template <typename... Ts>
    bool any_of(uint32_t const entity)
    {
        STREAMLINE_ASSERT(sizeof...(Ts) > 0);

        // extract the first component array
        sparse_set &entities = static_cast<sparse_set &>(*(pool.get<std::tuple_element_t<0, std::tuple<Ts...>>>()));

        // perform a union on all following sets
        ((const_cast<sparse_set &>(entities) =
              const_cast<sparse_set &>(entities).join(static_cast<sparse_set &>(*pool.get<Ts>()))),
         ...);

        return entities.search(entity) != sparse_set::null;
    }

    template <typename... Ts>
    bool all_of(uint32_t const entity)
    {
        STREAMLINE_ASSERT(sizeof...(Ts) > 0);

        // extract the first component array
        sparse_set &entities = static_cast<sparse_set &>(*(pool.get<std::tuple_element_t<0, std::tuple<Ts...>>>()));

        // perform an intersection on all following sets
        ((const_cast<sparse_set &>(entities) =
              const_cast<sparse_set &>(entities).intersect(static_cast<sparse_set &>(*pool.get<Ts>()))),
         ...);

        return entities.search(entity) != sparse_set::null;
    }
};

} // namespace engine