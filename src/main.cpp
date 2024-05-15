#include <engine/application/application.hpp>
#include <engine/camera/orthographic/orthographic.hpp>
#include <engine/camera/perspective/perspective.hpp>
#include <engine/mesh/object/object.hpp>
#include <engine/mesh/pyramid/pyramid.hpp>
#include <engine/world/world.hpp>

engine::Application application; // global external

int main(int argc, char const *argv[])
{
    engine::Window window(800, 600, "Streamline Engine");
    engine::PerspectiveCamera perspective_camera;
    engine::OrthographicCamera orthographic_camera;
    engine::World world("Overworld");

    engine::Object torus_0("Torus 0", "resources/objects/torus.obj");
    engine::Object torus_1("Torus 1", "resources/objects/torus.obj");
    engine::Object torus_2("Torus 2", "resources/objects/torus.obj");

    application.set_window(&window);

    application.add_camera(0, &perspective_camera);
    application.add_camera(1, &orthographic_camera);
    application.set_camera(1);

    application.add_world(0, &world);

    application.bind_movement_key(GLFW_KEY_W, engine::CameraDirection::Forward);
    application.bind_movement_key(GLFW_KEY_S, engine::CameraDirection::Backward);
    application.bind_movement_key(GLFW_KEY_A, engine::CameraDirection::Left);
    application.bind_movement_key(GLFW_KEY_D, engine::CameraDirection::Right);
    application.bind_movement_key(GLFW_KEY_SPACE, engine::CameraDirection::Up);
    application.bind_movement_key(GLFW_KEY_LEFT_SHIFT, engine::CameraDirection::Down);

    orthographic_camera.set_yaw(-45.0f);
    orthographic_camera.set_pitch(36.0f);

    torus_1.set_position(glm::vec3(10.0f, 5.0f, 0.0f));
    torus_2.set_position(glm::vec3(-10.0f, -5.0f, 0.0f));

    torus_0.add_child(&torus_1);
    torus_0.add_child(&torus_2);

    world.add_mesh(&torus_0);

    application.run();

    return 0;
}
