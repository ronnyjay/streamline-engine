#include "engine.hpp" // IWYU pragma: keep

using namespace engine;

int main(void)
{
    Application app;

    auto        s  = app.getSceneManager()->createScene();

    auto        e1 = s->create();
    auto        e2 = s->create();
    auto        e3 = s->create();
    auto        e4 = s->create();
    auto        e5 = s->create();

    s->emplace<Transform>(e1);
    s->emplace<Transform>(e2);
    s->emplace<Transform>(e3);
    s->emplace<Transform>(e4);
    s->emplace<Transform>(e5);

    s->emplace<PlayerController>(e1);
    s->emplace<PlayerInput>(e1);
    s->emplace<PlayerMove>(e1);
    s->emplace<PlayerLook>(e1);

    auto model = app.getResourceManager()->getModel("../assets/objects/cube/cube.obj");
    auto floor = app.getResourceManager()->getModel("../assets/objects/plane/plane.obj");

    s->emplace<Renderable>(e2, model);
    s->emplace<AABB>(e2, model);
    s->emplace<RigidBody>(e2);

    s->emplace<Renderable>(e3, floor);
    s->emplace<AABB>(e3, model);
    s->emplace<RigidBody>(e3);

    s->emplace<Cuboid>(e2, 1.0, 1.0, 1.0);
    s->emplace<Cuboid>(e3, 2.0, 2.0, 2.0);

    auto &body         = s->get<RigidBody>(e3);
    body.mass          = 0.0f;

    auto &camera       = s->emplace<Camera>(e1);
    camera.b_isPrimary = true;

    app.run();

    return 0;
}