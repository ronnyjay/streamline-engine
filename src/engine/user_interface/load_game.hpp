#pragma once

#include "engine/shader/shader.hpp"
#include "engine/user_interface/ui_element.hpp"
#include <engine/user_interface/user_interface.hpp>
#include <iostream>

class load_game : public engine::user_interface
{

  public:
    load_game(engine::shader_program &m_text_shader)
      : m_title(m_text_shader)
      , m_new_game_button(m_text_shader)
      , m_back_button(m_text_shader)
    {
        m_title.set_pos(0.0f, 0.5f);
        m_title.set_text("Load Game");

        m_new_game_button.set_pos(0.0f, -0.2f);
        m_new_game_button.set_text("New Game");
        m_new_game_button.on_click(
            [&](engine::click_data c)
            {
                m_new_game_button.set_text("New Game");
            });
        m_new_game_button.on_hover(
            [&](bool hovering)
            {
                if (hovering)
                    m_new_game_button.set_text(">New Game");
                else
                    m_new_game_button.set_text("New Game");
            });

        m_back_button.set_pos(0.0f, -0.4f);
        m_back_button.set_text("Back");
        m_back_button.on_click(
            [&](engine::click_data c)
            {
                m_on_back();
                m_back_button.set_text("Back");
            });
        m_back_button.on_hover(
            [&](bool hovering)
            {
                if (hovering)
                    m_back_button.set_text(">Back");
                else
                    m_back_button.set_text("Back");
            });

        add_element(&m_title);
        add_element(&m_new_game_button);
        add_element(&m_back_button);
    }

    void on_back(std::function<void()> f)
    {
        m_on_back = f;
    }

  private:
    engine::shader_program m_text_shader;
    engine::text_element m_title;
    engine::text_element m_new_game_button;
    engine::text_element m_back_button;

    std::function<void()> m_on_back;
};
