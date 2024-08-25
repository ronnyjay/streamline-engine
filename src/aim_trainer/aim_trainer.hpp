#pragma once

#include "engine/game/game.hpp"
#include "libstreamline/debug/logger.hpp"

class aim_trainer : public engine::game
{
  public:
    aim_trainer()
        : engine::game()
        , m_log("aim_trainer")
    {
    }

    ~aim_trainer() = default;

    void update(double) override;
    void render(double) override;

  private:
    logger m_log;
};
