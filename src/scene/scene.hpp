#pragma once

#include "core/debug.hpp"
#include "core/event.hpp"

#include "components.hpp"           // IWYU pragma: keep
#include "components/camera.hpp"    // IWYU pragma: keep
#include "components/id.hpp"        // IWYU pragma: keep
#include "components/input.hpp"     // IWYU pragma: keep
#include "components/transform.hpp" // IWYU pragma: keep

#include <entt/entity/registry.hpp>

#include <string>

namespace engine
{

class Entity;

class Scene : public Debuggable
{
  public:
    /**
     * @brief Construct a new Scene object
     *
     */
    Scene()
    {
    }

    /**
     * @brief
     *
     * @param e
     */
    void on_event(Event &e);

    /**
     * @brief
     *
     * @param dt
     */
    void step(float dt);

    /**
     * @brief
     *
     */
    void render();

    /**
     * @brief
     *
     * @param width
     * @param height
     */
    void on_viewport_resize(uint16_t width, uint16_t height);

    ~Scene()                         = default;

    Scene(const Scene &)             = delete;
    Scene(const Scene &&)            = delete;

    Scene &operator=(const Scene &)  = delete;
    Scene &operator=(const Scene &&) = delete;

    DEBUGGABLE()

  public:
    friend class Entity;

    /**
     * @brief Create an entity
     *
     * @return Entity
     */
    Entity create_entity(const std::string &);

  private:
    entt::registry m_registry;
};

}; // namespace engine