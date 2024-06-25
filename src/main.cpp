#include <engine/Application/Application.hpp>
#include <engine/Camera/Orthographic.hpp>
#include <engine/Camera/Perspective.hpp>
#include <engine/Entity/Entity.hpp>
#include <engine/ResourceManager/ResourceManager.hpp>

#include <engine/Components/AABB.hpp>
#include <engine/Components/Model.hpp>
#include <engine/Components/RigidBody.hpp>
#include <engine/Components/Transform.hpp>

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

    auto cubeModel = engine::ResourceManager::GetReference().Get<engine::Model>(cubeModelPath);
    auto torusModel = engine::ResourceManager::GetReference().Get<engine::Model>(torusModelPath);
    auto pyramidModel = engine::ResourceManager::GetReference().Get<engine::Model>(pyramidModelPath);
    auto sphereModel = engine::ResourceManager::GetReference().Get<engine::Model>(sphereModelPath);

    auto cube = scene.get()->CreateEntity("Cube");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");
    auto redLight = scene.get()->CreateEntity("Red Light Source");
    auto greenLight = scene.get()->CreateEntity("Green Light Source");
    auto blueLight = scene.get()->CreateEntity("Blue Light Source");

    cube.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
    cube.AddComponent<engine::AABB>(cubeModel);
    cube.AddComponent<engine::RigidBody>();
    cube.GetComponent<engine::Transform>().SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
    cube.GetComponent<engine::RigidBody>().SetInverseMass(0.0f);

    torus.AddComponent<std::shared_ptr<engine::Model>>(torusModel);
    torus.AddComponent<engine::AABB>(torusModel);
    torus.AddComponent<engine::RigidBody>();
    torus.GetComponent<engine::Transform>().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    pyramid.AddComponent<std::shared_ptr<engine::Model>>(pyramidModel);
    pyramid.AddComponent<engine::AABB>(pyramidModel);
    pyramid.AddComponent<engine::RigidBody>();
    pyramid.GetComponent<engine::Transform>().SetPosition(glm::vec3(-10.0f, 0.0f, 0.0f));

    redLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    redLight.AddComponent<engine::Light>(glm::vec4(1.0, 0.0, 0.0, 1.0));
    redLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(-10.0f, -10.0f, 0.0f));

    greenLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    greenLight.AddComponent<engine::Light>(glm::vec4(0.0, 1.0, 0.0, 1.0));
    greenLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(1.0f, -10.0f, 0.0f));

    blueLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    blueLight.AddComponent<engine::Light>(glm::vec4(0.0, 0.0, 1.0, 1.0));
    blueLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(10.0f, -5.0f, 0.0f));

    application.Run();

    return 0;
}
