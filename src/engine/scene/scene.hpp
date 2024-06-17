#pragma once

#include <engine/debug/debuggable.hpp>
#include <engine/physics/force_generator.hpp>

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
        : m_ForceGenerator(glm::vec3(0.0f, -9.81f, 0.0f))
    {
    }

    Entity CreateEntity(const std::string &);
    Entity CreateChildEntity(const Entity &parent, const std::string &);

    void DestroyEntity(const Entity);

  private:
    entt::registry m_Registry;

    ConstantForceGenerator m_ForceGenerator;

    friend class Application;
    friend class Entity;

    void Update(const float);
    void UpdateEntity(const entt::entity &, const glm::mat4 &);

    void Draw();
    void DrawEntity(const entt::entity &, const glm::mat4 &);

    void DrawDebugInfo() override;
    void DrawEntityDebugInfo(const entt::entity &);
};

}; // namespace engine