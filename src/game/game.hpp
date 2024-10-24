#pragma once

#include "core/event.hpp" // IWYU pragma: keep

#include "game/actor.hpp" // IWYU pragma: keep
#include "game/world.hpp" // IWYU pragma: keep

#include <memory>

namespace engine
{

class GameInstance
{
  public:
    /**
     * @brief
     *
     */
    virtual void update() = 0;

    /**
     * @brief
     *
     */
    virtual void render() = 0;

    /**
     * @brief
     *
     * @param e
     */
    virtual void on_resize(WindowResizeEvent &e)
    {
    }

    /**
     * @brief
     *
     * @param e
     */
    virtual void on_key_press(KeyPressEvent &e)
    {
    }

    /**
     * @brief
     *
     * @param e
     */
    virtual void on_mouse_press(MousePressEvent &e)
    {
    }

    /**
     * @brief
     *
     * @param e
     */
    virtual void on_mouse_move(MouseMoveEvent &e)
    {
    }

    /**
     * @brief
     *
     * @param e
     */
    virtual void on_mouse_scroll(MouseScrollEvent &e)
    {
    }

  private:
    std::shared_ptr<World> m_world_context;
};

}; // namespace engine