#include <engine/application/application.hpp>
#include <engine/collider/collider.hpp>
#include <engine/entity/entity.hpp>
#include <engine/logger/logger.hpp>
#include <engine/model/model.hpp>
#include <engine/scene/scene.hpp>

#include <engine/components/children.hpp>
#include <engine/components/identifier.hpp>
#include <engine/components/parent.hpp>
#include <engine/components/transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

extern Application application;

Entity Scene::CreateEntity(const std::string &identifier)
{
    Entity entity(m_Registry.create(), this);

    entity.AddComponent<Identifier>(identifier);
    entity.AddComponent<Parent>();
    entity.AddComponent<Children>();
    entity.AddComponent<Transform>();

    Logger::info("Entity created: \"%s\".\n", identifier.c_str());

    return entity;
}

Entity Scene::CreateChildEntity(const Entity &parent, const std::string &identifier)
{
    Entity child = CreateEntity(identifier);

    auto &childrenComponent = m_Registry.get<Children>(parent);
    auto &parentComponent = m_Registry.get<Parent>(child);

    childrenComponent.Emplace(child);
    parentComponent.Set(parent);

    Logger::info("Entity created as child: \"%s\".\n", identifier.c_str());

    return child;
}

void Scene::DestroyEntity(const Entity entity)
{
    auto &identifierComponent = m_Registry.get<Identifier>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    for (auto child : childrenComponent.Get())
    {
        DestroyEntity(Entity(child, this));
    }

    m_Registry.destroy(entity);

    Logger::info("Entity destroyed: \"%s\".\n", identifierComponent.Get().c_str());
}

void Scene::Update(const double deltaTime)
{
    // Propogate transformation updates
    auto view = m_Registry.view<Transform, Parent, Children>();

    for (auto entity : view)
    {
        if (view.get<Parent>(entity).Get() == entt::null)
        {
            UpdateEntity(entity, glm::mat4(1.0f));
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

void Scene::UpdateEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto &transformComponent = m_Registry.get<Transform>(entity);
    auto &childrenComponent = m_Registry.get<Children>(entity);

    auto *modelComponent = m_Registry.try_get<Model>(entity);
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

                for (const auto &mesh : modelComponent->GetMeshes())
                {
                    for (const auto &vertex : mesh.GetVertices())
                    {
                        vertices.push_back(glm::vec3(
                            (boundingTransform * glm::vec4(vertex.Position.x, vertex.Position.y, vertex.Position.z, 1.0f))));
                    }
                }

                boundingComponent->Update(vertices);
            }

            boundingComponent->Translate(boundingTranslation);
        }
    }

    for (auto &child : childrenComponent.Get())
    {
        auto &childTransformComponent = m_Registry.get<Transform>(child);

        if (transformComponent.IsDirty())
        {
            childTransformComponent.SetDirty(true);

            if (transformComponent.IsTranslationChanged())
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
    if (transformComponent.IsTranslationChanged())
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
    auto view = m_Registry.view<Model, Transform, Parent, Children>();
    auto lights = m_Registry.view<Light, Transform>();

    auto numLightsInShader = std::min(lights.size_hint(), Shader::MAX_NUM_LIGHTS);

    std::array<ShaderLight, Shader::MAX_NUM_LIGHTS> selectedLights;

    // TODO: get closest/strongest lights first, up to max size shader supports
    // Currently just grabs first because it's easy
    auto it_lights = lights.begin();
    for (size_t i = 0; i < Shader::MAX_NUM_LIGHTS; i++)
    {
        if (it_lights != lights.end())
        {
            auto &light = m_Registry.get<Light>(*it_lights);
            auto &pos = m_Registry.get<Transform>(*it_lights);

            selectedLights[i].pos = glm::vec4(pos.GetTranslation(), 1.0f);
            selectedLights[i].properties = light;

            it_lights++;
        }
        else
        {
            selectedLights[i] = ShaderLight{glm::vec4(0.0), {glm::vec4(0.0)}};
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
        if (view.get<Parent>(entity).Get() == entt::null)
        {
            DrawEntity(entity, glm::mat4(1.0f));
        }
    }
}

void Scene::DrawEntity(const entt::entity &entity, const glm::mat4 &transform)
{
    auto [modelComponent, transformComponent] = m_Registry.get<Model, Transform>(entity);

    auto modelMatrix = transformComponent.GetTransform() * transform;
    auto modelShader = application.GetShader("Model");
    auto &colliderShader = application.GetShader("Collider");

    modelShader.Use();
    modelShader.SetMat4("model", modelMatrix);
    modelComponent.Draw(modelShader);

    if (auto *boundingComponent = m_Registry.try_get<AABB>(entity))
    {
        if (application.Flags().ShowCollisions)
        {
            colliderShader.Use();
            colliderShader.SetBool("colliding", boundingComponent->GetColliding());

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

void Scene::DrawEntityDebugInfo(const entt::entity &entity)
{
    auto [identifierComponent, transformComponent, childrenComponent] = m_Registry.get<Identifier, Transform, Children>(entity);

    auto translation = transformComponent.GetTranslation();
    auto rotation = transformComponent.GetRotation();
    auto scale = transformComponent.GetScale();

    if (ImGui::TreeNode(identifierComponent.Get().c_str()))
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

    transformComponent.SetTranslation(translation);
    transformComponent.SetRotation(rotation);
    transformComponent.SetScale(scale);
}
