#pragma once

#include "actor.hpp"

namespace engine
{

struct PlayerController;

/**
 * @brief Designed to be possesed and controlled by a controller (Player, AI)
 *
 */
struct Pawn : public Actor
{
    /**
     * @brief
     *
     */
    Pawn()
    {
    }

    /**
     * @brief
     *
     * @param value
     */
    virtual void add_yaw_input(float value) {};

    /**
     * @brief
     *
     * @param value
     */
    virtual void add_pitch_input(float value) {};

    /**
     * @brief
     *
     * @param direction
     * @param value
     */
    virtual void add_movement_input(const glm::vec3 &direction, float value) {};

    /**
     * @brief
     *
     */
    virtual void set_controller_input_component(/** PlayerInputComponent */){};

  private:
    PlayerController *m_controller = nullptr;
};

} // namespace engine