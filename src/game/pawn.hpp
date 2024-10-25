#pragma once

#include "actor.hpp"
#include "component.hpp"

namespace engine
{

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

    PlayerInputComponent *InputComponent;

    /**
     * @brief
     *
     * @param value
     */
    virtual void move_forward(float value)
    {
    }

    /**
     * @brief
     *
     * @param value
     */
    virtual void move_right(float value) {};

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
};

} // namespace engine