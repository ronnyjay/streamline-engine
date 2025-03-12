#pragma once

#include "entity.hpp"                      // IWYU pragma: keep
#include "registry.hpp"                    // IWYU pragma: keep

#include "components/player_input.hpp"     // IWYU pragma: keep
#include "components/player_look.hpp"      // IWYU pragma: keep
#include "components/player_move.hpp"      // IWYU pragma: keep

#include "systems/camera_system.hpp"       // IWYU pragma: keep
#include "systems/controller_system.hpp"   // IWYU pragma: keep
#include "systems/player_input_system.hpp" // IWYU pragma: keep

namespace engine
{

struct scene
{
    friend struct player_input_system;
    friend struct controller_system;
    friend struct camera_system;

    scene()
    {
    }

    void draw();

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
    registry m_registry;
    camera_system m_cameraSystem;
    controller_system m_controllerSystem;
    player_input_system m_playerInputSystem;
};

} // namespace engine