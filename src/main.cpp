#include <engine/application/application.hpp>
#include <engine/camera/orthographic.hpp>
#include <engine/camera/perspective.hpp>
#include <engine/collider/collider.hpp>
#include <engine/components/transform.hpp>
#include <engine/entity/entity.hpp>
#include <engine/model/model.hpp>

engine::Application application(800, 600, "Streamline Engine");

int main(int argc, char const *argv[])
{
    auto scene = std::make_shared<engine::Scene>();

    auto perspectiveCamera = std::make_shared<engine::PerspectiveCamera>();
    auto orthographicCamera = std::make_shared<engine::OrthographicCamera>();

    application.AddScene(0, scene);

    application.AddCamera(0, perspectiveCamera);
    application.AddCamera(1, orthographicCamera);
    application.SetCamera(0);

    application.BindMovementKey(GLFW_KEY_W, engine::Direction::Forward);
    application.BindMovementKey(GLFW_KEY_S, engine::Direction::Backward);
    application.BindMovementKey(GLFW_KEY_A, engine::Direction::Left);
    application.BindMovementKey(GLFW_KEY_D, engine::Direction::Right);
    application.BindMovementKey(GLFW_KEY_SPACE, engine::Direction::Up);
    application.BindMovementKey(GLFW_KEY_LEFT_SHIFT, engine::Direction::Down);

    auto cube = scene.get()->CreateEntity("Cube");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");

    cube.AddComponent<engine::Model>("resources/objects/cube/cube.obj");
    cube.AddComponent<engine::AABB>();
    cube.GetComponent<engine::Transform>().SetTranslation(glm::vec3(-10.0f, 5.0f, 0.0f));

    torus.AddComponent<engine::Model>("resources/objects/torus/torus.obj");
    torus.AddComponent<engine::AABB>();
    torus.GetComponent<engine::Transform>().SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

    pyramid.AddComponent<engine::Model>("resources/objects/pyramid/pyramid.obj");
    pyramid.AddComponent<engine::AABB>();
    pyramid.GetComponent<engine::Transform>().SetTranslation(glm::vec3(10.0f, -5.0f, 0.0f));

    application.Run();

    return 0;
}
