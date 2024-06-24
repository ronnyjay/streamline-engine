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

    const std::string cubeModelPath = "resources/objects/cube/cube.obj";
    const std::string torusModelPath = "resources/objects/torus/torus.obj";
    const std::string pyramidModelPath = "resources/objects/pyramid/pyramid.obj";
    const std::string sphereModelPath = "resources/objects/sphere/sphere.obj";
    const std::string backpackModelPath = "resources/objects/backpack/backpack.obj";

    auto cubeModel = engine::ResourceManager::GetReference().Get<engine::Model>(cubeModelPath);
    auto torusModel = engine::ResourceManager::GetReference().Get<engine::Model>(torusModelPath);
    auto pyramidModel = engine::ResourceManager::GetReference().Get<engine::Model>(pyramidModelPath);
    auto sphereModel = engine::ResourceManager::GetReference().Get<engine::Model>(sphereModelPath);
    auto backpackModel = engine::ResourceManager::GetReference().Get<engine::Model>(backpackModelPath);

    auto backpack = scene.get()->CreateEntity("Backpack");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");
    auto redLight = scene.get()->CreateEntity("Red Light Source");
    auto greenLight = scene.get()->CreateEntity("Green Light Source");
    auto blueLight = scene.get()->CreateEntity("Blue Light Source");

    backpack.AddComponent<std::shared_ptr<engine::Model>>(backpackModel);
    backpack.AddComponent<engine::AABB>(backpackModel);
    backpack.GetComponent<engine::Transform>().setPosition(glm::vec3(-10.0f, 5.0f, 0.0f));

    torus.AddComponent<std::shared_ptr<engine::Model>>(torusModel);
    torus.AddComponent<engine::AABB>(torusModel);
    torus.GetComponent<engine::Transform>().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    pyramid.AddComponent<std::shared_ptr<engine::Model>>(pyramidModel);
    pyramid.AddComponent<engine::AABB>(pyramidModel);
    pyramid.GetComponent<engine::Transform>().setPosition(glm::vec3(10.0f, -2.0f, 0.0f));

    redLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    redLight.AddComponent<engine::Light>(glm::vec4(1.0, 0.0, 0.0, 1.0));
    redLight.GetComponent<engine::Transform>().setPosition(glm::vec3(-10.0f, -10.0f, 0.0f));

    greenLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    greenLight.AddComponent<engine::Light>(glm::vec4(0.0, 1.0, 0.0, 1.0));
    greenLight.GetComponent<engine::Transform>().setPosition(glm::vec3(1.0f, -10.0f, 0.0f));

    blueLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    blueLight.AddComponent<engine::Light>(glm::vec4(0.0, 0.0, 1.0, 1.0));
    blueLight.GetComponent<engine::Transform>().setPosition(glm::vec3(10.0f, -5.0f, 0.0f));

    application.Run();

    return 0;
}
