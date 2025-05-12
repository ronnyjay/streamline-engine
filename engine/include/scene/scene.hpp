#pragma once

#include "entity.hpp"                      // IWYU pragma: keep
#include "registry.hpp"                    // IWYU pragma: keep

#include "components/aabb.hpp"             // IWYU pragma: keep
#include "components/camera.hpp"           // IWYU pragma: keep
#include "components/controller.hpp"       // IWYU pragma: keep
#include "components/follow.hpp"           // IWYU pragma: keep
#include "components/identifier.hpp"       // IWYU pragma: keep
#include "components/light.hpp"            // IWYU pragma: keep
#include "components/look_at.hpp"          // IWYU pragma: keep
#include "components/orbit.hpp"            // IWYU pragma: keep
#include "components/player_input.hpp"     // IWYU pragma: keep
#include "components/player_look.hpp"      // IWYU pragma: keep
#include "components/player_move.hpp"      // IWYU pragma: keep
#include "components/renderable.hpp"       // IWYU pragma: keep
#include "components/transform.hpp"        // IWYU pragma: keep

#include "systems/camera_system.hpp"       // IWYU pragma: keep
#include "systems/collision_system.hpp"    // IWYU pragma: keep
#include "systems/controller_system.hpp"   // IWYU pragma: keep
#include "systems/follow_system.hpp"       // IWYU pragma: keep
#include "systems/lighting_system.hpp"     // IWYU pragma: keep
#include "systems/player_input_system.hpp" // IWYU pragma: keep

#include "subsystems/resource_manager.hpp"

namespace engine
{

struct Scene
{
    friend struct ComponentSystem;
    friend struct PlayerInputSystem;
    friend struct ControllerSystem;
    friend struct CollisionSystem;
    friend struct LightingSystem;
    friend struct FollowSystem;
    friend struct CameraSystem;

    Scene()
        : m_cameraSystem(this)
        , m_followSystem(this)
        , m_collisionSystem(this)
        , m_controllerSystem(this)
        , m_playerInputSystem(this)

    {
        m_shader = ResourceManager::getInstance().getShader("Model", "../assets/shaders/model.vs",
                                                            "../assets/shaders/model.fs");
        m_aabbShader =
            ResourceManager::getInstance().getShader("AABB", "../assets/shaders/AABB.vs", "../assets/shaders/AABB.fs");
    }

    void                      draw();

    void                      tick(double dt);

    [[nodiscard]] entity_type create() const
    {
        return m_registry.create();
    }

    template <typename T, typename... Args>
    T &emplace(const entity_type e, Args &&...args)
    {
        return m_registry.emplace<T>(e, std::forward<Args>(args)...);
    }

    template <typename T>
    T &get(const entity_type entity)
    {
        return m_registry.get<T>(entity);
    }

    void onWindowResize(uint32_t width, uint32_t height)
    {
        m_cameraSystem.updateAspectRatios(width, height);
    }

  private:
    Registry                m_registry;
    CameraSystem            m_cameraSystem;
    FollowSystem            m_followSystem;
    CollisionSystem         m_collisionSystem;
    ControllerSystem        m_controllerSystem;
    PlayerInputSystem       m_playerInputSystem;
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Shader> m_aabbShader;
};

} // namespace engine