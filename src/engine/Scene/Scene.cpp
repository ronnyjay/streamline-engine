#include "engine/Components/Animator.hpp"
#include <engine/Application/Application.hpp>

#include <engine/Entity/Entity.hpp>
#include <engine/Logger/Logger.hpp>
#include <engine/Scene/Scene.hpp>

#include <engine/Components/AABB.hpp>
#include <engine/Components/Children.hpp>
#include <engine/Components/Identifier.hpp>
#include <engine/Components/Light.hpp>
#include <engine/Components/Model.hpp>
#include <engine/Components/Parent.hpp>
#include <engine/Components/RigidBody.hpp>
#include <engine/Components/Transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iterator>
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
    auto physicsView = m_Registry.view<RigidBody, Transform>();

    // Integrate acceleration
    for (auto entity : physicsView)
    {
        RigidBody &body = physicsView.get<RigidBody>(entity);
        Transform &transform = physicsView.get<Transform>(entity);

        glm::vec3 acceleration = body.GetForce() * body.GetInverseMass();

        if (body.GetInverseMass() > 0)
        {
            acceleration += glm::vec3(0.0f, -9.81f, 0.0f);
        }

        glm::vec3 linearVelocity = body.GetLinearVelocity();

        glm::vec3 k1 = dt * acceleration;
        glm::vec3 k2 = dt * (acceleration + k1 * 0.5f);
        glm::vec3 k3 = dt * (acceleration + k2 * 0.5f);
        glm::vec3 k4 = dt * (acceleration + k3);

        linearVelocity += (k1 + 2.0f * k2 + 2.0f * k3 + k4) / 6.0f;

        body.SetLinearVelocity(linearVelocity);
    }

    // Detect collisions
    auto collisionView = m_Registry.view<AABB>();

    for (auto a = collisionView.begin(); a != collisionView.end(); ++a)
    {
        for (auto b = std::next(a); b != collisionView.end(); ++b)
        {
            auto &colliderA = collisionView.get<AABB>(*a);
            auto &colliderB = collisionView.get<AABB>(*b);
        }
    }

    // Integrate velocity
    for (auto entity : physicsView)
    {
        RigidBody &body = physicsView.get<RigidBody>(entity);
        Transform &transform = physicsView.get<Transform>(entity);

        glm::vec3 linearVelocity = body.GetLinearVelocity();

        glm::vec3 k1 = dt * linearVelocity;
        glm::vec3 k2 = dt * (linearVelocity + k1 * 0.5f);
        glm::vec3 k3 = dt * (linearVelocity + k2 * 0.5f);
        glm::vec3 k4 = dt * (linearVelocity + k3);

        linearVelocity += (k1 + 2.0f * k2 + 2.0f * k3 + k4) / 6.0f;

        body.SetLinearVelocity(linearVelocity);
    }

    // Integrate position
    for (auto entity : physicsView)
    {
        RigidBody &rigidBody = physicsView.get<RigidBody>(entity);
        Transform &transform = physicsView.get<Transform>(entity);

        transform.SetPosition(transform.GetPosition() + rigidBody.GetLinearVelocity() * dt);
    }

    // Update transforms
    auto transformView = m_Registry.view<Transform, Parent, Children>();

    for (auto entity : transformView)
    {
        if (transformView.get<Parent>(entity).parent == entt::null)
        {
            UpdateEntity(entity, glm::mat4(1.0f));
        }
    }
}

void Scene::UpdateEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto &transformComponent = m_Registry.get<Transform>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    auto *modelComponent = m_Registry.try_get<std::shared_ptr<Model>>(entity);
    auto *boundingComponent = m_Registry.try_get<AABB>(entity);

    auto modelMatrix = transformComponent.GetTransform() * transform;

    if (modelComponent && boundingComponent)
    {
        if (transformComponent.IsDirty())
        {
            // Isolate translation
            glm::vec3 boundingTranslation(modelMatrix[3]);

            if (transformComponent.IsRotationChanged() || transformComponent.IsScaleChanged())
            {
                // Remove translation from transform
                glm::mat4 boundingTransform(modelMatrix[0], modelMatrix[1], modelMatrix[2], glm::vec4(0, 0, 0, 1));

                std::vector<glm::vec3> vertices;

                for (const auto &mesh : modelComponent->get()->GetMeshes())
                {
                    for (const auto &vertex : mesh.GetVertices())
                    {
                        vertices.push_back(glm::vec3(
                            (boundingTransform *
                             glm::vec4(vertex.Position.x, vertex.Position.y, vertex.Position.z, 1.0f))));
                    }
                }

                boundingComponent->Update(vertices);
            }

            boundingComponent->Translate(boundingTranslation);
        }
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

void Scene::Draw(const double deltaTime)
{
    auto view = m_Registry.view<std::shared_ptr<Model>, Transform, Parent, Children>();
    auto lights = m_Registry.view<Light, Transform>();

    auto numLightsInShader = std::min(lights.size_hint(), ShaderProgram::MAX_NUM_LIGHTS);

    std::array<Light, ShaderProgram::MAX_NUM_LIGHTS> selectedLights;

    // TODO: get closest/strongest lights first, up to max size shader supports
    // Currently just grabs first because it's easy
    auto it_lights = lights.begin();
    for (size_t i = 0; i < numLightsInShader; i++)
    {
        if (it_lights != lights.end())
        {
            auto &position = m_Registry.get<Transform>(*it_lights);
            auto &light = m_Registry.get<Light>(*it_lights);

            selectedLights[i].color = light.color;
            selectedLights[i].position = (glm::vec4(position.GetPosition(), 1.0f));
            // selectedLights[i].properties = properties;
            it_lights++;
        }
    }

    auto modelShader = application.GetShader("Model");
    modelShader.Use();
    modelShader.UpdateLights(selectedLights);
    modelShader.SetUInt("NumLights", numLightsInShader);

    auto camera = application.GetCurrentCamera();
    auto projectionMatrix = camera->ProjectionMatrix();
    auto viewMatrix = camera->ViewMatrix();

    modelShader.SetMat4("projection", projectionMatrix);
    modelShader.SetMat4("view", viewMatrix);
    modelShader.SetVec3("viewPos", camera->GetPosition());

    auto colliderShader = application.GetShader("Collider");
    colliderShader.Use();

    colliderShader.SetMat4("projection", projectionMatrix);
    colliderShader.SetMat4("view", viewMatrix);

    for (auto entity : view)
    {
        if (view.get<Parent>(entity).parent == entt::null)
        {
            // if object has an animator, update time step and get bone matrices
            if (auto animator_sp = m_Registry.try_get<std::shared_ptr<Animator>>(entity))
            {
                auto animator = *animator_sp;
                animator->UpdateAnimation(deltaTime);
                auto transforms = animator->GetFinalBoneMatrices();
                for (uint i = 0; i < transforms.size(); ++i)
                    modelShader.SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
            }
            DrawEntity(entity, glm::mat4(1.0f));
        }
    }
}

void Scene::DrawEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto [modelComponent, transformComponent] = m_Registry.get<std::shared_ptr<Model>, Transform>(entity);

    auto modelMatrix = transformComponent.GetTransform() * transform;
    auto modelShader = application.GetShader("Model");
    auto &colliderShader = application.GetShader("Collider");

    modelShader.Use();

    modelShader.SetMat4("model", modelMatrix);
    modelComponent->Draw(modelShader);

    if (auto *boundingComponent = m_Registry.try_get<AABB>(entity))
    {
        if (application.Flags().ShowCollisions)
        {
            colliderShader.Use();
            colliderShader.SetBool("colliding", boundingComponent->GetColliding());

            boundingComponent->Draw();
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
