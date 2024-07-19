#include <engine/Application/Application.hpp>

#include <engine/Entity/Entity.hpp>
#include <engine/Logger/Logger.hpp>
#include <engine/Scene/Scene.hpp>

#include <engine/Components/AABB.hpp>
#include <engine/Components/BSphere.hpp>
#include <engine/Components/BVolume.hpp>
#include <engine/Components/Children.hpp>
#include <engine/Components/Identifier.hpp>
#include <engine/Components/Light.hpp>
#include <engine/Components/Model.hpp>
#include <engine/Components/Parent.hpp>
#include <engine/Components/RigidBody.hpp>
#include <engine/Components/Transform.hpp>

#include <engine/Physics/Collision.hpp>

#include <glm/ext/vector_float4.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iterator>
#include <variant>
#include <vector>

using namespace engine;

extern Application application;

Entity Scene::CreateEntity(const std::string &identifier)
{
    Entity entity(m_Registry.create(), this);

    entity.AddComponent<Identifier>(identifier);
    entity.AddComponent<Parent>();
    entity.AddComponent<Children>();
    entity.AddComponent<Transform>();

    Logger::Info("Entity created: \"%s\".\n", identifier.c_str());

    return entity;
}

Entity Scene::CreateChildEntity(const Entity &parent, const std::string &identifier)
{
    Entity child = CreateEntity(identifier);

    auto &childrenComponent = m_Registry.get<Children>(parent);
    auto &parentComponent = m_Registry.get<Parent>(child);

    childrenComponent.children.emplace_back(child);
    parentComponent.parent = parent;

    Logger::Info("Entity created as child: \"%s\".\n", identifier.c_str());

    return child;
}

void Scene::DestroyEntity(const Entity entity)
{
    auto &identifierComponent = m_Registry.get<Identifier>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    for (auto child : childrenComponent.children)
    {
        DestroyEntity(Entity(child, this));
    }

    m_Registry.destroy(entity);

    Logger::Info("Entity destroyed: \"%s\".\n", identifierComponent.identifier.c_str());
}

void Scene::Update(const float dt)
{
    auto transformView = m_Registry.view<Parent, Children, Transform>();

    for (auto entity : transformView)
    {
        if (transformView.get<Parent>(entity).parent == entt::null)
        {
            UpdateEntity(entity, glm::mat4(1.0f));
        }
    }

    auto physicsView = m_Registry.view<BoundingVolume, RigidBody, Transform>();

    for (auto entity : physicsView)
    {
        RigidBody &body = physicsView.get<RigidBody>(entity);
        Transform &transform = physicsView.get<Transform>(entity);

        body.UpdateInertiaTensor(transform.GetRotation());

        glm::vec3 acceleration = body.GetForce() * body.GetInverseMass();
        glm::vec3 angularAcceleration = body.GetInertiaTensor() * body.GetTorque();

        if (body.GetInverseMass() > 0)
        {
            acceleration += glm::vec3(0.0f, -9.81f, 0.0f);
        }

        body.SetLinearVelocity(body.GetLinearVelocity() + acceleration * dt);
        body.SetAngularVelocity(body.GetAngularVelocity() + angularAcceleration * dt);
    }

    for (auto a = physicsView.begin(); a != physicsView.end(); ++a)
    {
        for (auto b = std::next(a); b != physicsView.end(); ++b)
        {
            auto &volumeA = physicsView.get<BoundingVolume>(*a);
            auto &volumeB = physicsView.get<BoundingVolume>(*b);

            if (std::visit(IntersectionVisitor{}, volumeA, volumeB))
            {
                CollisionResult collisionResult = std::visit(CollisionVisitor{}, volumeA, volumeB);

                RigidBody &bodyA = physicsView.get<RigidBody>(*a);
                RigidBody &bodyB = physicsView.get<RigidBody>(*b);

                Transform &transformA = physicsView.get<Transform>(*a);
                Transform &transformB = physicsView.get<Transform>(*b);

                bool isBoxA = std::holds_alternative<AABB>(volumeA);
                bool isBoxB = std::holds_alternative<AABB>(volumeB);

                // Box has been hit by sphere, negate normal
                if ((!isBoxA || !isBoxB) && (isBoxA || isBoxB))
                {
                    if (isBoxA)
                    {
                        collisionResult.normal = -collisionResult.normal;
                    }
                }

                float totalMass = bodyA.GetInverseMass() + bodyB.GetInverseMass();

                transformA.SetPosition(
                    transformA.GetPosition() -
                    collisionResult.normal * collisionResult.penetration * (bodyA.GetInverseMass() / totalMass));

                transformB.SetPosition(
                    transformB.GetPosition() +
                    collisionResult.normal * collisionResult.penetration * (bodyB.GetInverseMass() / totalMass));

                glm::vec3 relativeA = collisionResult.position - transformA.GetPosition();
                glm::vec3 relativeB = collisionResult.position - transformB.GetPosition();

                glm::vec3 angularVelocityA = glm::cross(bodyA.GetAngularVelocity(), relativeA);
                glm::vec3 angularVelocityB = glm::cross(bodyB.GetAngularVelocity(), relativeB);

                glm::vec3 fullVelocityA = bodyA.GetLinearVelocity() + angularVelocityA;
                glm::vec3 fullVelocityB = bodyB.GetLinearVelocity() + angularVelocityB;

                glm::vec3 contactVelocity = fullVelocityB - fullVelocityA;

                glm::vec3 inertiaA =
                    glm::cross(bodyA.GetInertiaTensor() * glm::cross(relativeA, collisionResult.normal), relativeA);

                glm::vec3 inertiaB =
                    glm::cross(bodyB.GetInertiaTensor() * glm::cross(relativeB, collisionResult.normal), relativeB);

                float angularEffect = glm::dot(inertiaA + inertiaB, collisionResult.normal);

                float e = (bodyA.GetElasticity() + bodyB.GetElasticity()) * 0.5f;

                float j =
                    (-(1.0f + e) * glm::dot(contactVelocity, collisionResult.normal)) / (totalMass + angularEffect);

                glm::vec3 fullImpulse = collisionResult.normal * j;

                bodyA.ApplyLinearImpulse(-fullImpulse);
                bodyB.ApplyLinearImpulse(fullImpulse);

                bodyA.ApplyAngularImpulse(glm::cross(relativeA, -fullImpulse));
                bodyB.ApplyAngularImpulse(glm::cross(relativeB, fullImpulse));
            }
        }
    }

    for (auto entity : physicsView)
    {
        RigidBody &body = physicsView.get<RigidBody>(entity);
        Transform &transform = physicsView.get<Transform>(entity);

        transform.SetPosition(transform.GetPosition() + body.GetLinearVelocity() * dt);
        transform.SetRotation(transform.GetRotation() + body.GetAngularVelocity() * dt);

        float dampingFactor = 1.0f - 0.95f;
        float frameDamping = std::pow(dampingFactor, dt);

        body.SetAngularVelocity(body.GetAngularVelocity() * frameDamping);
    }
}

void Scene::UpdateEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto &transformComponent = m_Registry.get<Transform>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    auto *modelComponent = m_Registry.try_get<std::shared_ptr<Model>>(entity);
    auto *boundingComponent = m_Registry.try_get<BoundingVolume>(entity);

    auto modelMatrix = transformComponent.GetTransform() * transform;

    if (modelComponent && boundingComponent && transformComponent.IsDirty())
    {
        // Get translation from transform
        glm::vec3 translation = modelMatrix[3];

        if (std::holds_alternative<AABB>(*boundingComponent))
        {
            if (transformComponent.IsRotationChanged() || transformComponent.IsScaleChanged())
            {
                // Remove translation from transform
                glm::mat4 matrix(modelMatrix[0], modelMatrix[1], modelMatrix[2], glm::vec4(0, 0, 0, 1));

                // Apply transform to vertices
                std::vector<glm::vec3> vertices;

                for (const auto &mesh : modelComponent->get()->GetMeshes())
                {
                    for (const auto &vertex : mesh.GetVertices())
                    {
                        vertices.push_back(glm::vec3(
                            matrix * glm::vec4(vertex.Position.x, vertex.Position.y, vertex.Position.z, 1.0f)));
                    }
                }

                std::visit([&vertices](auto &volume) { volume.Update(vertices); }, *boundingComponent);
            }
        }

        if (std::holds_alternative<BSphere>(*boundingComponent))
        {
            if (transformComponent.IsScaleChanged())
            {
                // Remove translation from transform
                glm::mat4 matrix(modelMatrix[0], modelMatrix[1], modelMatrix[2], glm::vec4(0, 0, 0, 1));

                // Apply transform to vertices
                std::vector<glm::vec3> vertices;

                for (const auto &mesh : modelComponent->get()->GetMeshes())
                {
                    for (const auto &vertex : mesh.GetVertices())
                    {
                        vertices.push_back(glm::vec3(
                            matrix * glm::vec4(vertex.Position.x, vertex.Position.y, vertex.Position.z, 1.0f)));
                    }
                }

                std::visit([&vertices](auto &volume) { volume.Update(vertices); }, *boundingComponent);
            }
        }

        std::visit([&translation](auto &volume) { volume.Translate(translation); }, *boundingComponent);
    }

    for (auto &child : childrenComponent.children)
    {
        auto &childTransformComponent = m_Registry.get<Transform>(child);

        if (transformComponent.IsDirty())
        {
            childTransformComponent.SetDirty(true);

            if (transformComponent.IsPositionChanged())
            {
                childTransformComponent.SetTranslationChanged(true);
            }

            if (transformComponent.IsRotationChanged())
            {
                childTransformComponent.SetRotationChanged(true);
            }

            if (transformComponent.IsScaleChanged())
            {
                childTransformComponent.SetScaleChanged(true);
            }
        }

        UpdateEntity(child, modelMatrix);
    }

    // Reset flags after updating children
    if (transformComponent.IsPositionChanged())
    {
        transformComponent.SetTranslationChanged(false);
    }

    if (transformComponent.IsRotationChanged())
    {
        transformComponent.SetRotationChanged(false);
    }

    if (transformComponent.IsScaleChanged())
    {
        transformComponent.SetScaleChanged(false);
    }

    if (transformComponent.IsDirty())
    {
        transformComponent.SetDirty(false);
    }
}

void Scene::Draw()
{
    auto view = m_Registry.view<std::shared_ptr<Model>, Transform, Parent, Children>();
    auto lights = m_Registry.view<Light, Transform>();

    auto numLightsInShader = std::min(lights.size_hint(), ShaderProgram::MAX_NUM_LIGHTS);

    std::array<Light, ShaderProgram::MAX_NUM_LIGHTS> selectedLights;

    auto it_lights = lights.begin();
    for (size_t i = 0; i < numLightsInShader; i++)
    {
        if (it_lights != lights.end())
        {
            auto &position = m_Registry.get<Transform>(*it_lights);
            auto &light = m_Registry.get<Light>(*it_lights);

            selectedLights[i].color = light.color;
            selectedLights[i].position = (glm::vec4(position.GetPosition(), 1.0f));
            it_lights++;
        }
    }

    auto camera = application.GetCurrentCamera();

    auto projectionMatrix = camera->ProjectionMatrix();
    auto viewMatrix = camera->ViewMatrix();
    auto viewPos = camera->GetPosition();

    auto modelShader = application.GetShader("Model");

    auto boxShader = application.GetShader("AABB");
    auto sphereShader = application.GetShader("BSphere");

    modelShader.Use();
    modelShader.UpdateLights(selectedLights);
    modelShader.SetUInt("NumLights", numLightsInShader);
    modelShader.SetMat4("projection", projectionMatrix);
    modelShader.SetMat4("view", viewMatrix);
    modelShader.SetVec3("viewPos", viewPos);

    boxShader.Use();
    boxShader.SetMat4("projection", projectionMatrix);
    boxShader.SetMat4("view", viewMatrix);

    sphereShader.Use();
    sphereShader.SetMat4("projection", projectionMatrix);
    sphereShader.SetMat4("view", viewMatrix);

    for (auto entity : view)
    {
        if (view.get<Parent>(entity).parent == entt::null)
        {
            DrawEntity(entity, glm::mat4(1.0f));
        }
    }
}

void Scene::DrawEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto [modelComponent, transformComponent] = m_Registry.get<std::shared_ptr<Model>, Transform>(entity);

    auto modelMatrix = transformComponent.GetTransform() * transform;
    auto modelShader = application.GetShader("Model");
    auto boxShader = application.GetShader("AABB");
    auto sphereShader = application.GetShader("BSphere");

    modelShader.Use();
    modelShader.SetMat4("model", modelMatrix);

    modelComponent->Draw(modelShader);

    if (auto *boundingComponent = m_Registry.try_get<BoundingVolume>(entity))
    {
        if (application.Flags().ShowCollisions)
        {

            if (std::holds_alternative<BSphere>(*boundingComponent))
            {
                sphereShader.Use();
                sphereShader.SetVec3("translation", modelMatrix[3]);
            }
            else
            {
                boxShader.Use();
            }

            std::visit([](auto &volume) { volume.Draw(); }, *boundingComponent);
        }
    }

    for (auto &child : m_Registry.get<Children>(entity).children)
    {
        DrawEntity(child, modelMatrix);
    }
}

void Scene::DrawDebugInfo()
{
    if (ImGui::TreeNode("Entities"))
    {
        auto view = m_Registry.view<Transform, Parent, Children>();

        for (auto entity : view)
        {
            if (view.get<Parent>(entity).parent == entt::null)
            {
                DrawEntityDebugInfo(entity);
            }
        }

        ImGui::TreePop();
    }
}

void Scene::DrawEntityDebugInfo(const entt::entity &entity)
{
    auto [identifierComponent, transformComponent, childrenComponent] =
        m_Registry.get<Identifier, Transform, Children>(entity);

    auto translation = transformComponent.GetPosition();
    auto rotation = transformComponent.GetRotation();
    auto scale = transformComponent.GetScale();

    if (ImGui::TreeNode(identifierComponent.identifier.c_str()))
    {
        ImGui::DragFloat("Translation X", &translation.x);
        ImGui::DragFloat("Translation Y", &translation.y);
        ImGui::DragFloat("Translation Z", &translation.z);
        ImGui::DragFloat("Rotation X", &rotation.x);
        ImGui::DragFloat("Rotation Y", &rotation.y);
        ImGui::DragFloat("Rotation Z", &rotation.z);
        ImGui::DragFloat("Scale X", &scale.x);
        ImGui::DragFloat("Scale Y", &scale.y);
        ImGui::DragFloat("Scale Z", &scale.z);

        if (ImGui::TreeNode((identifierComponent.identifier + " Children").c_str()))
        {
            for (auto &child : childrenComponent.children)
            {
                DrawEntityDebugInfo(child);
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }

    transformComponent.SetPosition(translation);
    transformComponent.SetRotation(rotation);
    transformComponent.SetScale(scale);
}
