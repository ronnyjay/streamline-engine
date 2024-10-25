#pragma once

#include "pawn.hpp"

namespace engine
{

/**
 * @brief Designed to possess and control a pawn via a player
 *
 */
struct PlayerController
{
    /**
     * @brief
     *
     */
    PlayerController()
    {
    }

    void posses(Pawn *handle)
    {
        if (handle != nullptr)
        {
            m_handle = handle;
        }
    }

  private:
    Pawn *m_handle;
};

/**
 * @brief Designed to possess and control a pawn through pre-defined logic
 *
 */
struct AIController
{
};

} // namespace engine