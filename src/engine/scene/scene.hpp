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
    Entity CreateChildEntity(Entity &, const std::string &);
    void DestroyEntity(Entity);

  private:
    entt::registry m_Registry;

    void Update(double);
    void UpdateEntity(entt::entity &, double);

    void Draw();
    void DrawEntity(entt::entity &, const glm::mat4 &transform);

    void DrawDebugInfo() override;
    void DrawEntityDebugInfo(entt::entity &);

    friend class Application;
    friend class Entity;
};

}; // namespace engine