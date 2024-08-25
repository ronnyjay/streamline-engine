#pragma once

#include "engine/game/game.hpp"

class aim_trainer : public engine::game
{
  public:
    aim_trainer()
        : engine::game()
    {
    }

    ~aim_trainer() = default;

    void update() override;
    void render(double) override;
};
