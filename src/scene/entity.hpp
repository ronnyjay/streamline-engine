#pragma once

#include "scene.hpp"

#include <entt/entity/entity.hpp>

namespace engine
{

class Scene;

class Entity
{

  public:
    using Handle = entt::entity;

    /**
     * @brief Construct a new Entity object
     *
     */
    Entity() = default;

    /**
     * @brief Construct a new Entity object
     *
     */
    Entity(Handle, Scene *);

    /**
     * @brief
     *
     * @return entt::entity
     */
    operator Handle() const
    {
        return m_handle;
    }

    bool operator==(const Entity &other) const;
    bool operator!=(const Entity &other) const;

    /**
     * @brief
     *
     * @tparam T
     * @return T&
     */
    template <typename T>
    T &get()
    {
        return m_scene->m_registry.get<T>(m_handle);
    }

    /**
     * @brief
     *
     * @tparam T
     * @tparam Args
     * @param args
     * @return T&
     */
    template <typename T, typename... Args>
    T &add(Args &&...args)
    {
        return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
    }

  private:
    Handle m_handle;
    Scene *m_scene;
};

} // namespace engine