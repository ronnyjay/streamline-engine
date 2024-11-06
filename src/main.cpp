#include "core/application.hpp"
#include <thread>

using namespace engine;

int main(void)
{
    Application &app = Application::Get();

    app.Run();

    return 0;
}