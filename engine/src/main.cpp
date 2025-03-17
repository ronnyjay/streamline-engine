#include "engine.hpp" // IWYU pragma: keep

using namespace engine;

int main(void)
{
    Application app;

    auto        s = app.getSceneManager()->createScene();

    auto        e1 = s->create();
    auto        e2 = s->create();
    auto        e3 = s->create();

    s->emplace<Transform>(e1);
    s->emplace<Transform>(e2);
    s->emplace<Transform>(e3);

    s->emplace<Renderable>(e1, "../assets/objects/cube/cube.obj");

    auto &f2 = s->emplace<Follow>(e1, e2);
    auto &f3 = s->emplace<Follow>(e3, e2);

    f2.b_ignorePitchRotation = true;
    f2.b_ignoreYawRotation = true;

    f3.offset = vec3(-5.0f, 2.0f, 0.0f);
    f3.b_ignoreYawRotation = true;
    f3.b_ignorePitchRotation = true;

    s->emplace<PlayerController>(e2);
    s->emplace<PlayerInput>(e2);
    s->emplace<PlayerMove>(e2);
    s->emplace<PlayerLook>(e2);

    s->emplace<Camera>(e3);

    app.run();

    return 0;
}