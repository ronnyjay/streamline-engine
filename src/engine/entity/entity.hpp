#pragma once

#include <engine/scene/scene.hpp>
#include <entt/entt.hpp>

namespace engine
{

class Entity
{
  public:
    Entity() = default;
    Entity(entt::entity, Scene *);
    Entity(const Entity &) = default;

    template <typename T, typename... Args>
    T &AddComponent(Args &&...args)
    {
        assert(!HasComponent<T>() && "Entity already has component!");
        return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
    }

    template <typename T>
    T &GetComponent()
    {
        assert(HasComponent<T>() && "Entity does not have component!");
        return m_Scene->m_Registry.get<T>(m_Handle);
    }

    template <typename T>
    bool HasComponent()
    {
        return m_Scene->m_Registry.all_of<T>(m_Handle);
    }

    template <typename T>
    void RemoveComponent()
    {
        assert(HasComponent<T>() && "Entity does not have component!");
        m_Scene->m_Registry.remove<T>(m_Handle);
    }

    operator entt::entity() const
    {
        return m_Handle;
    }

    bool operator==(const Entity &other) const
    {
        return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
    }

    bool operator!=(const Entity &other) const
    {
        return (this != &other);
    }

  private:
    entt::entity m_Handle;
    Scene *m_Scene;
};

}; // namespace engine