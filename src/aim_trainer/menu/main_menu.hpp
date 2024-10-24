#pragma once

#include <engine/glfw3.h>
#include <engine/user_interface/ui_element.hpp>
#include <engine/user_interface/user_interface.hpp>
#include <functional>

class main_menu : public engine::user_interface
{

  public:
    main_menu(engine::shader_program &text_shader)
        : m_title(text_shader)
        , m_play_button(text_shader)
        , m_quit_button(text_shader)
        , m_should_quit(false)
    {
        m_title.set_pos(0.0f, 0.5f);
        m_title.set_text("Aim Trainer");

        m_on_play = [] {};

        m_play_button.set_text("Play");
        m_play_button.set_pos(0.0f, 0.0f);
        m_play_button.on_click([&](engine::click_data c) { m_on_play(); });

        m_play_button.on_hover(
            [&](bool hovering)
            {
                if (hovering)
                    m_play_button.set_text(">Play");
                else
                    m_play_button.set_text("Play");
            });

        m_quit_button.set_pos(0.0f, -0.2f);
        m_quit_button.set_text("Quit");
        m_quit_button.on_click(
            [&](engine::click_data c)
            {
                if (c.action == GLFW_PRESS)
                    m_should_quit = true;
            });
        m_quit_button.on_hover(
            [&](bool hovering)
            {
                if (hovering)
                    m_quit_button.set_text(">Quit");
                else
                    m_quit_button.set_text("Quit");
            });

        add_element(&m_title);
        add_element(&m_play_button);
        add_element(&m_quit_button);
    }

    bool should_quit()
    {
        return m_should_quit;
    }

    void on_play(std::function<void()> f)
    {
        m_on_play = f;
    }

    virtual ~main_menu()
    {
    }

  private:
    engine::text_element m_title;
    engine::text_element m_play_button;
    engine::text_element m_quit_button;

    std::function<void()> m_on_play;

    bool m_should_quit;
};
