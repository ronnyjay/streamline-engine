#include "core/application.hpp"

using namespace engine;

int main(void)
{
    Application &app = Application::Get();

    app.GetTopLevelWindow()->set_window_mode(WindowMode::Fullscreen);

    app.Run();

    return 0;
}