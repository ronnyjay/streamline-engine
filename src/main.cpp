#include "core/application.hpp"

using namespace engine;

int main(void)
{
    Application &app = Application::get();

    app.run();

    return 0;
}