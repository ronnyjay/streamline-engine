#include "core/application.hpp"

using namespace engine;

int main(void)
{
    Application &app = Application::Get();

    app.Run();

    return 0;
}