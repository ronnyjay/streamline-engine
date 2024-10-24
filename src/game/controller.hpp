#pragma once

#include "pawn.hpp"

#include <memory>

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

    void posses(std::shared_ptr<Pawn> context)
    {
        m_pawn_context = context;
    }

  private:
    std::shared_ptr<Pawn> m_pawn_context;
};

/**
 * @brief Designed to possess and control a pawn through pre-defined logic
 *
 */
struct AIController
{
};

} // namespace engine