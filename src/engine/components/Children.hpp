#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace engine
{

class Children
{
  public:
    Children() = default;
    Children(const Children &) = default;

    std::vector<entt::entity> &Get()
    {
        return m_Children;
    }

    void Emplace(const entt::entity child)
    {
        m_Children.emplace_back(child);
    }

  private:
    std::vector<entt::entity> m_Children;
};

}; // namespace engine