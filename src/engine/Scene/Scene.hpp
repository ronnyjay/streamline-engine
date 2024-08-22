#pragma once

#include <engine/Debug/Debuggable.hpp>

#include <entt/entity/registry.hpp>

#include <glm/glm.hpp>

namespace engine
{

class Application;
class Entity;

class Scene : public Debuggable
{
  public:
    Scene()
    {
    }

    Entity CreateEntity(const std::string &);

    Entity CreateChildEntity(const Entity &parent, const std::string &);

    void DestroyEntity(const Entity);

  private:
    entt::registry m_Registry;

    friend class Application;
    friend class Entity;

    void Update(const float);
    void UpdateEntity(const entt::entity &, const glm::mat4 &);

    void Draw();
    void DrawEntity(const entt::entity &, const glm::mat4 &);

    void draw_debug_info() override;
    void DrawEntityDebugInfo(const entt::entity &);
};

} // namespace engine