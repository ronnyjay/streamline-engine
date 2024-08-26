#include "aim_trainer.hpp"
#include "engine/game/game.hpp"

#include <engine/glfw3.h>
#include <chrono>
#include <thread>

void aim_trainer::update(double dt)
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(15));
}

void aim_trainer::render(double dt)
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    m_menu.render();
}

void aim_trainer::window_size_changed(const unsigned int width, const unsigned int height)
{
    m_menu.set_dimensions(width, height);
}

void aim_trainer::mouse_press(const int button, int action, int mods)
{
    // use a switch depending on which ui is active?
    m_menu.mouse_press(button, action, m_mouse_pos.x, m_mouse_pos.y);
}

void aim_trainer::mouse_pos(const double x, const double y)
{
    engine::game::mouse_pos(x, y);

    // use a switch depending on which ui is active?
    m_menu.mouse_pos(x, y);
}
