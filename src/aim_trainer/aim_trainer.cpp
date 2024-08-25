#include "aim_trainer.hpp"

#include <engine/glfw3.h>
#include <chrono>
#include <thread>

void aim_trainer::update(double dt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
}

void aim_trainer::render(double dt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    m_menu.render();
}

void aim_trainer::window_size_changed(const unsigned int width, const unsigned int height)
{
    m_menu.set_dimensions(width, height);
}
