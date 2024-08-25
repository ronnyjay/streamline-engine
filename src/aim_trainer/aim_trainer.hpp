#pragma once

#include <libstreamline/debug/logger.hpp>

#include <engine/game/game.hpp>
#include <engine/shader/shader.hpp>

#include "aim_trainer/menu/main_menu.hpp"

class aim_trainer : public engine::game
{
  public:
    aim_trainer()
        : engine::game()
        , m_log("aim_trainer")
        , m_text_shader()
        , m_menu(m_text_shader)
    {
    }

    ~aim_trainer() = default;

    void update(double) override;
    void render(double) override;
    void window_size_changed(const unsigned int width, const unsigned int height) override;

  private:
    logger m_log;

    engine::shader_program m_text_shader;
    main_menu m_menu;
};
