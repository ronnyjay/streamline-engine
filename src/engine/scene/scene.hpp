#pragma once

#include <engine/debug/debuggable.hpp>
#include <entt/entity/registry.hpp>

#include <glm/glm.hpp>

#include <unordered_map>

namespace engine
{

class Application;
class Entity;

class Scene : public Debuggable
{
  public:
    Scene();

    Entity CreateEntity(const std::string &);
    Entity CreateChildEntity(const Entity &, const std::string &);
    void DestroyEntity(const Entity);

  private:
    entt::registry m_Registry;

    void Update(const double);
    void UpdateEntity(const entt::entity &, const double);

    void Draw();
    void DrawEntity(const entt::entity &, const glm::mat4 &transform);

    void DrawDebugInfo() override;
    void DrawEntityDebugInfo(const entt::entity &);

    friend class Application;
    friend class Entity;
};

}; // namespace engine