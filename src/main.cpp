#include "engine/resource_manager/resource_manager.hpp"
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

    auto backpack = scene.get()->CreateEntity("Backpack");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");
    auto light1 = scene.get()->CreateEntity("Light Source");
    auto light2 = scene.get()->CreateEntity("Light Source 2");
    auto light3 = scene.get()->CreateEntity("Light Source 3");

    auto backpackModel = engine::resource_manager::get_reference().Get<engine::Model>("resources/objects/backpack/backpack.obj");
    auto cubeModel = engine::resource_manager::get_reference().Get<engine::Model>("resources/objects/cube/cube.obj");
    auto torusModel = engine::resource_manager::get_reference().Get<engine::Model>("resources/objects/torus/torus.obj");
    auto pyramidModel = engine::resource_manager::get_reference().Get<engine::Model>("resources/objects/pyramid/pyramid.obj");

    backpack.AddComponent<std::shared_ptr<engine::Model>>(backpackModel);
    backpack.AddComponent<engine::AABB>();
    backpack.GetComponent<engine::Transform>().SetTranslation(glm::vec3(-10.0f, 5.0f, 0.0f));

    torus.AddComponent<std::shared_ptr<engine::Model>>(torusModel);
    torus.AddComponent<engine::AABB>();
    torus.GetComponent<engine::Transform>().SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

    pyramid.AddComponent<std::shared_ptr<engine::Model>>(pyramidModel);
    pyramid.AddComponent<engine::AABB>();
    pyramid.GetComponent<engine::Transform>().SetTranslation(glm::vec3(10.0f, -2.0f, 0.0f));

    light1.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
    light1.AddComponent<engine::Light>(glm::vec4(1.0, 0.0, 0.0, 1.0));
    light1.GetComponent<engine::Transform>().SetTranslation(glm::vec3(-10.0f, -10.0f, 0.0f));

    light2.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
    light2.AddComponent<engine::Light>(glm::vec4(0.0, 1.0, 0.0, 1.0));
    light2.GetComponent<engine::Transform>().SetTranslation(glm::vec3(1.0f, -10.0f, 0.0f));

    light3.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
    light3.AddComponent<engine::Light>(glm::vec4(0.0, 0.0, 1.0, 1.0));
    light3.GetComponent<engine::Transform>().SetTranslation(glm::vec3(10.0f, -5.0f, 0.0f));

    application.Run();

    return 0;
}
