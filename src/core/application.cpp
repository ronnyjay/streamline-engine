#include "application.hpp"

using namespace engine;

std::unique_ptr<Application> Application::kInstance = nullptr;

Application &Application::get()
{
    if (!kInstance)
    {
        kInstance = std::unique_ptr<Application>(new Application);
    }

    return *kInstance;
}

void Application::run()
{
    return;
}