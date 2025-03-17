#include "engine.hpp" // IWYU pragma: keep

using namespace engine;

int main(void)
{
    Application app;

    auto s = app.getSceneManager()->createScene();

    app.run();

    return 0;
}