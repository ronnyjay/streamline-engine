#include "application.hpp"

using namespace engine;

std::unique_ptr<Application> Application::kInstance = nullptr;

Application::Application()
{
    mWindow = Window::Create(800, 600, "Streamline Engine");
}

void Application::Run()
{
    return;
}

Application::~Application()
{
}