#pragma once

#include "entity.hpp"                      // IWYU pragma: keep
#include "registry.hpp"                    // IWYU pragma: keep

#include "components/camera.hpp"           // IWYU pragma: keep
#include "components/controller.hpp"       // IWYU pragma: keep
#include "components/identifier.hpp"       // IWYU pragma: keep
#include "components/player_input.hpp"     // IWYU pragma: keep
#include "components/player_look.hpp"      // IWYU pragma: keep
#include "components/player_move.hpp"      // IWYU pragma: keep
#include "components/renderable.hpp"       // IWYU pragma: keep
#include "components/transform.hpp"        // IWYU pragma: keep

#include "systems/camera_system.hpp"       // IWYU pragma: keep
#include "systems/controller_system.hpp"   // IWYU pragma: keep
#include "systems/player_input_system.hpp" // IWYU pragma: keep

#include "subsystems/resource_manager.hpp"

namespace engine
{

struct scene
{
    friend struct PlayerInputSystem;
    friend struct ControllerSystem;
    friend struct CameraSystem;

    scene()
        : m_cameraSystem(this)
        , m_controllerSystem(this)
        , m_playerInputSystem(this)

    {
        m_shader = ResourceManager::getInstance().getShader("Model", "../assets/shaders/model.vs",
                                                            "../assets/shaders/model.fs");
    }

    void draw() const;

    void tick(double dt);

    [[nodiscard]] entity_type create() const
    {
        return m_registry.create();
    }

    template <typename T, typename... Args>
    T &emplace(const entity_type e, Args &&...args)
    {
        return m_registry.emplace<T>(e, std::forward<Args>(args)...);
    }

  private:
    registry                m_registry;
    CameraSystem            m_cameraSystem;
    ControllerSystem        m_controllerSystem;
    PlayerInputSystem       m_playerInputSystem;
    std::shared_ptr<Shader> m_shader;
};

} // namespace engine