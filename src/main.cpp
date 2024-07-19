#include <engine/Application/Application.hpp>
#include <engine/Camera/Orthographic.hpp>
#include <engine/Camera/Perspective.hpp>
#include <engine/Entity/Entity.hpp>
#include <engine/ResourceManager/ResourceManager.hpp>

#include <engine/Components/AABB.hpp>
#include <engine/Components/BSphere.hpp>
#include <engine/Components/BVolume.hpp>
#include <engine/Components/Model.hpp>
#include <engine/Components/RigidBody.hpp>
#include <engine/Components/Transform.hpp>
#include <memory>
#include <string>
#include <sys/types.h>

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
    const std::string planeModelPath = "resources/objects/plane/plane.obj";

    auto cubeModel = engine::ResourceManager::GetReference().Get<engine::Model>(cubeModelPath);
    auto torusModel = engine::ResourceManager::GetReference().Get<engine::Model>(torusModelPath);
    auto pyramidModel = engine::ResourceManager::GetReference().Get<engine::Model>(pyramidModelPath);
    auto sphereModel = engine::ResourceManager::GetReference().Get<engine::Model>(sphereModelPath);
    auto planeModel = engine::ResourceManager::GetReference().Get<engine::Model>(planeModelPath);

    auto cube = scene.get()->CreateEntity("Cube");
    auto torus = scene.get()->CreateEntity("Torus");
    auto pyramid = scene.get()->CreateEntity("Pyramid");
    auto sphere = scene.get()->CreateEntity("Sphere");
    auto plane = scene.get()->CreateEntity("Plane");
    auto redLight = scene.get()->CreateEntity("Red Light Source");
    auto greenLight = scene.get()->CreateEntity("Green Light Source");
    auto blueLight = scene.get()->CreateEntity("Blue Light Source");

    for (int i = 0; i < 2; i++)
    {
        auto obj = scene.get()->CreateEntity("Object" + std::to_string(i));

        if (!(i % 2))
        {
            obj.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
            obj.AddComponent<engine::BoundingVolume>(engine::AABB(cubeModel));
            obj.AddComponent<engine::RigidBody>();
            obj.GetComponent<engine::Transform>().SetPosition(glm::vec3(-1.0f, 110.0f + (i * 5.0f), 0.0f));
            obj.GetComponent<engine::RigidBody>().InitSphereInertia(obj.GetComponent<engine::Transform>().GetScale());
        }
        else
        {
            obj.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
            obj.AddComponent<engine::BoundingVolume>(engine::BSphere(sphereModel));
            obj.AddComponent<engine::RigidBody>();
            obj.GetComponent<engine::Transform>().SetPosition(glm::vec3(-1.0f, 110.0f + (i * 5.0f), 0.0f));
            obj.GetComponent<engine::RigidBody>().InitSphereInertia(obj.GetComponent<engine::Transform>().GetScale());
        }
    }

    for (int i = 0; i < 2; i++)
    {
        auto obj = scene.get()->CreateEntity("Object" + std::to_string(i));

        if ((i % 2))
        {
            obj.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
            obj.AddComponent<engine::BoundingVolume>(engine::AABB(cubeModel));
            obj.AddComponent<engine::RigidBody>();
            obj.GetComponent<engine::Transform>().SetPosition(glm::vec3(1.0f, 110.0f + (i * 5.0f), 0.0f));
            obj.GetComponent<engine::RigidBody>().InitSphereInertia(obj.GetComponent<engine::Transform>().GetScale());
        }
        else
        {
            obj.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
            obj.AddComponent<engine::BoundingVolume>(engine::BSphere(sphereModel));
            obj.AddComponent<engine::RigidBody>();
            obj.GetComponent<engine::Transform>().SetPosition(glm::vec3(1.0f, 110.0f + (i * 5.0f), 0.0f));
            obj.GetComponent<engine::RigidBody>().InitSphereInertia(obj.GetComponent<engine::Transform>().GetScale());
        }
    }

    cube.AddComponent<std::shared_ptr<engine::Model>>(cubeModel);
    cube.AddComponent<engine::BoundingVolume>(engine::AABB(cubeModel));
    cube.AddComponent<engine::RigidBody>();
    cube.GetComponent<engine::Transform>().SetPosition(glm::vec3(5.0f, 25.0f, 0.0f));
    cube.GetComponent<engine::RigidBody>().InitCubeInertia(cube.GetComponent<engine::Transform>().GetScale());

    torus.AddComponent<std::shared_ptr<engine::Model>>(torusModel);
    torus.AddComponent<engine::BoundingVolume>(engine::BSphere(torusModel));
    torus.AddComponent<engine::RigidBody>();
    torus.GetComponent<engine::Transform>().SetPosition(glm::vec3(3.8f, 100.0f, 0.0f));
    torus.GetComponent<engine::RigidBody>().InitCubeInertia(torus.GetComponent<engine::Transform>().GetScale());

    pyramid.AddComponent<std::shared_ptr<engine::Model>>(pyramidModel);
    pyramid.AddComponent<engine::BoundingVolume>(engine::AABB(pyramidModel));
    pyramid.AddComponent<engine::RigidBody>();
    pyramid.GetComponent<engine::Transform>().SetPosition(glm::vec3(-5.0f, 100.0f, 0.0f));
    pyramid.GetComponent<engine::RigidBody>().InitCubeInertia(pyramid.GetComponent<engine::Transform>().GetScale());

    sphere.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    sphere.AddComponent<engine::BoundingVolume>(engine::BSphere(sphereModel));
    sphere.AddComponent<engine::RigidBody>();
    sphere.GetComponent<engine::Transform>().SetPosition(glm::vec3(-2.0f, 100.0f, 0.0f));
    sphere.GetComponent<engine::RigidBody>().InitSphereInertia(sphere.GetComponent<engine::Transform>().GetScale());

    plane.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    plane.AddComponent<engine::BoundingVolume>(engine::BSphere(sphereModel));
    plane.AddComponent<engine::RigidBody>();
    plane.GetComponent<engine::Transform>().SetPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    plane.GetComponent<engine::Transform>().SetScale(glm::vec3(10.0f, 10.0f, 10.0f));
    plane.GetComponent<engine::RigidBody>().SetInverseMass(0.0f);
    plane.GetComponent<engine::RigidBody>().InitCubeInertia(plane.GetComponent<engine::Transform>().GetScale());

    redLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    redLight.AddComponent<engine::Light>(glm::vec4(1.0, 0.0, 0.0, 1.0));
    redLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(-10.0f, 10.0f, 0.0f));

    greenLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    greenLight.AddComponent<engine::Light>(glm::vec4(0.0, 1.0, 0.0, 1.0));
    greenLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(1.0f, 10.0f, 0.0f));

    blueLight.AddComponent<std::shared_ptr<engine::Model>>(sphereModel);
    blueLight.AddComponent<engine::Light>(glm::vec4(0.0, 0.0, 1.0, 1.0));
    blueLight.GetComponent<engine::Transform>().SetPosition(glm::vec3(10.0f, 10.0f, 0.0f));

    perspectiveCamera.get()->SetPosition(glm::vec3(0.0f, 0.0f, -50.0f));

    application.ShowCollisions(true);

    application.Run();

    return 0;
}
