#include "engine.hpp" // IWYU pragma: keep

using namespace engine;

int main(void)
{
    Application app;

    auto s = app.getSceneManager()->createScene();

    auto e1 = s->create();
    auto e2 = s->create();

    s->emplace<Transform>(e1);
    s->emplace<Transform>(e2);

    s->emplace<Renderable>(e1, "../assets/objects/cube/cube.obj");

    s->emplace<PlayerController>(e2);
    s->emplace<PlayerInput>(e2);
    s->emplace<PlayerMove>(e2);
    s->emplace<PlayerLook>(e2);
    s->emplace<Camera>(e2);

    app.run();

    return 0;
}