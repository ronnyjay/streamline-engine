#include "aim_trainer.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include <ratio>
#include <thread>

void aim_trainer::update(double dt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
}

void aim_trainer::render(double dt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
