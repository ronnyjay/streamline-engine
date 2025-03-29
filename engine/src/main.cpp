#include "engine.hpp" // IWYU pragma: keep
#include "scene/components/controller.hpp"
#include "scene/components/look_at.hpp"

using namespace engine;

int main(void)
{
    Application app;

    auto        s = app.getSceneManager()->createScene();

    auto        e1 = s->create();
    auto        e2 = s->create();
    auto        e3 = s->create();
    auto        e4 = s->create();

    s->emplace<Transform>(e1);
    s->emplace<Transform>(e2);
    s->emplace<Transform>(e3);
    s->emplace<Transform>(e4);

    s->emplace<Renderable>(e1, "../assets/objects/cube/cube.obj");
    s->emplace<Renderable>(e4, "../assets/objects/plane/plane.obj");

    s->emplace<Follow>(e1, e2);
    s->emplace<Follow>(e3, e2);

    s->emplace<PlayerController>(e2);
    s->emplace<PlayerInput>(e2);
    s->emplace<PlayerMove>(e2);
    s->emplace<PlayerLook>(e2);

    s->emplace<Camera>(e3);
    s->emplace<LookAt>(e3, e1);
    // s->emplace<Orbit>(e3);

    auto &f1 = s->get<Follow>(e1);
    auto &f3 = s->get<Follow>(e3);
    auto &c3 = s->get<Camera>(e3);

    f1.b_ignorePitchRotation = true;
    f1.b_ignoreYawRotation   = false;
    f1.b_invertPitchRotation = true;
    f1.b_invertYawRotation   = true;

    f1.pitchDamping = 0.0125f;
    f1.yawDamping   = 0.0125f;

    f3.b_ignorePitchRotation = true;
    f3.b_ignoreYawRotation   = true;

    f3.offset = vec3(0.0f, 2.0f, -5.0f);

    c3.b_isPrimary = true;

    app.run();

    return 0;
}