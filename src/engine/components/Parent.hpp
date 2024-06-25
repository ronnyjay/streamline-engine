#pragma once

#include <entt/entt.hpp>

namespace engine
{

class Parent
{
  public:
    Parent()
        : m_Parent(entt::null)
    {
    }

    Parent(const Parent &) = default;

    const entt::entity Get() const
    {
        return m_Parent;
    }

    void Set(const entt::entity parent)
    {
        if (parent != m_Parent)
        {
            m_Parent = parent;
        }
    }

  private:
    entt::entity m_Parent;
};

}; // namespace engine