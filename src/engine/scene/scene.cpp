#include <engine/application/application.hpp>
#include <engine/collider/collider.hpp>
#include <engine/components/components.hpp>
#include <engine/entity/entity.hpp>
#include <engine/model/model.hpp>
#include <engine/scene/scene.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

extern Application application;

Scene::Scene()
{
}

Entity Scene::CreateEntity(const std::string &identifier)
{
    Entity entity(m_Registry.create(), this);

    entity.AddComponent<Identifier>(identifier);
    entity.AddComponent<Parent>();
    entity.AddComponent<Children>();
    entity.AddComponent<Transform>();

    return entity;
}

Entity Scene::CreateChildEntity(Entity &parent, const std::string &identifier)
{
    Entity child = CreateEntity(identifier);

    auto &childrenComponent = m_Registry.get<Children>(parent);
    auto &parentComponent = m_Registry.get<Parent>(child);

    childrenComponent.Emplace(child);
    parentComponent.Set(parent);

    return child;
}

void Scene::DestroyEntity(Entity entity)
{
    auto &childrenComponent = m_Registry.get<Children>(entity);

    for (auto child : childrenComponent.Get())
    {
        DestroyEntity(Entity(child, this));
    }

    m_Registry.destroy(entity);
}

void Scene::Update(double deltaTime)
{
    // Propogate transformation updates
    auto view = m_Registry.view<Transform, Parent, Children>();

    for (auto entity : view)
    {
        if (view.get<Parent>(entity).Get() == entt::null)
        {
            UpdateEntity(entity, deltaTime);
        }
    }

    // Check for collisions
    std::set<AABB *> collisions;

    m_Registry.view<AABB>().each(
        [&](auto entityA, AABB &aabbA)
        {
            m_Registry.view<AABB>().each(
                [&](auto entityB, AABB &aabbB)
                {
                    if (entityA < entityB && aabbA.Intersects(aabbB))
                    {
                        collisions.insert(&aabbA);
                        collisions.insert(&aabbB);
                    }
                });
        });

    for (auto &entity : m_Registry.view<AABB>())
    {
        auto &boundingComponent = m_Registry.get<AABB>(entity);

        if (collisions.find(&boundingComponent) != collisions.end())
        {
            boundingComponent.SetColliding(true);
        }
        else
        {
            boundingComponent.SetColliding(false);
        }
    }
}

void Scene::UpdateEntity(entt::entity &entity, double deltaTime)
{
    auto &transformComponent = m_Registry.get<Transform>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    for (auto &child : childrenComponent.Get())
    {
        auto &childTransformComponent = m_Registry.get<Transform>(child);

        if (transformComponent.IsDirty())
        {
            childTransformComponent.SetDirty(true);
        }

        UpdateEntity(child, deltaTime);
    }
}

void Scene::Draw()
{
    auto view = m_Registry.view<Model, Transform, Parent, Children>();

    for (auto entity : view)
    {
        if (view.get<Parent>(entity).Get() == entt::null)
        {
            DrawEntity(entity, glm::mat4(1.0f));
        }
    }
}

void Scene::DrawEntity(entt::entity &entity, const glm::mat4 &transform)
{
    auto [modelComponent, transformComponent] = m_Registry.get<Model, Transform>(entity);

    auto camera = application.GetCurrentCamera();
    auto shader = application.GetShader("Model");

    auto projectionMatrix = camera->ProjectionMatrix();
    auto viewMatrix = camera->ViewMatrix();
    auto modelMatrix = transformComponent.GetTransform() * transform;

    shader.Use();
    shader.SetMat4("projection", projectionMatrix);
    shader.SetMat4("view", viewMatrix);
    shader.SetMat4("model", modelMatrix);

    modelComponent.Draw(shader);

    if (auto *boundingComponent = m_Registry.try_get<AABB>(entity))
    {
        if (transformComponent.IsDirty())
        {
            std::vector<glm::vec3> vertices;

            for (const auto &mesh : modelComponent.GetMeshes())
            {
                for (const auto &vertex : mesh.GetVertices())
                {
                    vertices.push_back(glm::vec3(
                        (modelMatrix * glm::vec4(vertex.Position.x, vertex.Position.y, vertex.Position.z, 1.0f))));
                }
            }

            boundingComponent->Update(vertices);

            transformComponent.SetDirty(false);
        }

        if (application.Flags().ShowCollisions)
        {
            shader = application.GetShader("Collider");

            shader.Use();
            shader.SetMat4("projection", projectionMatrix);
            shader.SetMat4("view", viewMatrix);
            shader.SetBool("colliding", boundingComponent->GetColliding());

            boundingComponent->Draw();
        }
    }

    for (auto &child : m_Registry.get<Children>(entity).Get())
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
            if (view.get<Parent>(entity).Get() == entt::null)
            {
                DrawEntityDebugInfo(entity);
            }
        }

        ImGui::TreePop();
    }
}

void Scene::DrawEntityDebugInfo(entt::entity &entity)
{
    auto [identifierComponent, transformComponent, childrenComponent] =
        m_Registry.get<Identifier, Transform, Children>(entity);

    auto position = transformComponent.GetPosition();
    auto rotation = transformComponent.GetRotation();
    auto scale = transformComponent.GetScale();

    if (ImGui::TreeNode(identifierComponent.Get().c_str()))
    {
        ImGui::DragFloat("Position X", &position.x);
        ImGui::DragFloat("Position Y", &position.y);
        ImGui::DragFloat("Position Z", &position.z);
        ImGui::DragFloat("Rotation X", &rotation.x);
        ImGui::DragFloat("Rotation Y", &rotation.y);
        ImGui::DragFloat("Rotation Z", &rotation.z);
        ImGui::DragFloat("Scale X", &scale.x);
        ImGui::DragFloat("Scale Y", &scale.y);
        ImGui::DragFloat("Scale Z", &scale.z);

        if (ImGui::TreeNode((identifierComponent.Get() + " Children").c_str()))
        {
            for (auto &child : childrenComponent.Get())
            {
                DrawEntityDebugInfo(child);
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }

    transformComponent.SetPosition(position);
    transformComponent.SetRotation(rotation);
    transformComponent.SetScale(scale);
}