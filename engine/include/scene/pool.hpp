#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "storage.hpp"

namespace engine
{

using dense_container = std::unordered_map<std::type_index, std::unique_ptr<sparse_set>>;

class component_storage_pool
{
    dense_container container;

  public:
    template <typename T>
    component_storage<T> *get()
    {
        const auto type_index = std::type_index(typeid(T));
        if (container.find(type_index) == container.end())
        {
            container[type_index] = std::make_unique<component_storage<T>>();
        }
        return static_cast<component_storage<T> *>(container[type_index].get());
    }

    void remove(uint32_t const entity)
    {
        for (auto &storage : container)
        {
            if (storage.second->search(entity) != sparse_set::null)
            {
                storage.second->remove(entity);
            }
        }
    }
};

} // namespace engine