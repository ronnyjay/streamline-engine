#include "engine/physics/force_accumulator.hpp"
#include "engine/physics/rigid_body.hpp"
#include "entt/entity/fwd.hpp"
#include <cstddef>
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

#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
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

void Scene::Update(const float dt)
{
    m_Registry.view<RigidBody, ForceAccumulator, Transform>().each(
        [&](RigidBody &rigidBody, ForceAccumulator &forceAccumulator, Transform &transform)
        {
            // Apply forces
            m_ForceGenerator.ApplyForce(rigidBody, forceAccumulator);

            // Integrate
            glm::vec3 initialPosition = transform.Position;
            glm::vec3 initialVelocity = rigidBody.Velocity;

            glm::vec3 acceleration = forceAccumulator.AccumulatedForces;

            glm::vec3 k1_p = initialVelocity;
            glm::vec3 k1_v = acceleration;

            glm::vec3 k2_p = initialVelocity + k1_v * (dt * 0.5f);
            glm::vec3 k2_v = acceleration;

            glm::vec3 k3_p = initialVelocity + k2_v * (dt * 0.5f);
            glm::vec3 k3_v = acceleration;

            glm::vec3 k4_p = initialVelocity + k3_v * (dt * 0.5f);
            glm::vec3 k4_v = acceleration;

            transform.Position = initialPosition + (k1_p + 2.0f * (k2_p + k3_p) + k4_p) * (dt / 6.0f);
            rigidBody.Velocity = initialVelocity + (k1_v + 2.0f * (k2_v + k3_v) + k4_v) * (dt / 6.0f);

            forceAccumulator.AccumulatedForces = glm::vec3(0.0f);
            rigidBody.Impulse = glm::vec3(0.0f);
        });

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
    std::set<std::pair<entt::entity, entt::entity>> collisions;

    auto collider_view = m_Registry.view<AABB>();
    auto colliders = std::vector(collider_view.begin(), collider_view.end());

    for (size_t i = 0; i < colliders.size(); i++)
    {
        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            auto &boxA = m_Registry.get<AABB>(colliders[i]);
            auto &boxB = m_Registry.get<AABB>(colliders[j]);

            if (boxA.Intersects(boxB))
            {
                collisions.insert(std::make_pair(colliders[i], colliders[j]));
            }
        }
    }

    for (auto &pair : collisions)
    {
        RigidBody *bodyA = m_Registry.try_get<RigidBody>(pair.first);
        RigidBody *bodyB = m_Registry.try_get<RigidBody>(pair.second);

        Transform &transformA = m_Registry.get<Transform>(pair.first);
        Transform &transformB = m_Registry.get<Transform>(pair.second);

        AABB &boxA = m_Registry.get<AABB>(pair.first);
        AABB &boxB = m_Registry.get<AABB>(pair.second);

        glm::vec3 aMin = boxA.Min();
        glm::vec3 aMax = boxA.Max();

        glm::vec3 bMin = boxB.Min();
        glm::vec3 bMax = boxB.Max();

        glm::vec3 halfWidthA = (aMax - aMin) * 0.5f;
        glm::vec3 halfWidthB = (bMax - bMin) * 0.5f;

        glm::vec3 centerA = (aMax + aMin) * 0.5f;
        glm::vec3 centerB = (bMax + bMin) * 0.5f;

        glm::vec3 collisionDepth = halfWidthA + halfWidthB - glm::abs(centerB - centerA);

        glm::vec3 collisionNormal;

        if (collisionDepth.x < collisionDepth.y && collisionDepth.x < collisionDepth.z)
        {
            collisionNormal = glm::vec3(1.0f, 0.0f, 0.0f) * glm::sign(centerB.x - centerA.x);
        }
        else if (collisionDepth.y < collisionDepth.x && collisionDepth.y < collisionDepth.z)
        {
            collisionNormal = glm::vec3(0.0f, 1.0f, 0.0f) * glm::sign(centerB.y - centerA.y);
        }
        else
        {
            collisionNormal = glm::vec3(0.0f, 0.0f, 1.0f) * glm::sign(centerB.z - centerA.z);
        }

        if (bodyA && bodyB)
        {
            float inverseMassA = 1 / bodyA->Mass;
            float inverseMassB = 1 / bodyB->Mass;

            float totalMass = inverseMassA + inverseMassB;

            transformA.Position -= collisionNormal * collisionDepth * (inverseMassA / totalMass);
            transformB.Position += collisionNormal * collisionDepth * (inverseMassB / totalMass);

            glm::vec3 contactVelocity = bodyB->Velocity - bodyA->Velocity;

            float e = (bodyA->Restitution + bodyB->Restitution) * 0.5f;
            float j = (-(1.0f + e) * glm::dot(contactVelocity, collisionNormal)) / totalMass;

            glm::vec3 impulse = collisionNormal * j;

            bodyA->Velocity -= impulse * inverseMassA;
            bodyB->Velocity += impulse * inverseMassB;
        }
        else if (bodyB)
        {
            glm::vec3 relativeVelocity = bodyB->Velocity;

            if (glm::length(relativeVelocity) > bodyB->RestitutionThreshold)
            {
                bodyB->Velocity = -bodyB->Restitution * relativeVelocity;
            }
            else
            {
                bodyB->Velocity = -bodyB->Velocity;
            }

            if (glm::length(bodyB->Velocity) < 1.0f)
            {
                bodyB->Velocity = glm::vec3(0.0f);
            }

            transformB.Position += collisionDepth * collisionNormal;
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
        if (transformComponent.Dirty())
        {
            // Isolate translation
            glm::vec3 boundingTranslation(modelMatrix[3]);

            if (transformComponent.Rotation.Changed || transformComponent.Scale.Changed)
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

    for (auto &child : childrenComponent.Get())
    {
        auto &childTransformComponent = m_Registry.get<Transform>(child);

        if (transformComponent.Dirty())
        {
            if (transformComponent.Position.Changed)
            {
                childTransformComponent.Position.Changed = true;
            }

            if (transformComponent.Rotation.Changed)
            {
                childTransformComponent.Rotation.Changed = true;
            }

            if (transformComponent.Scale.Changed)
            {
                childTransformComponent.Scale.Changed = true;
            }
        }

        UpdateEntity(child, modelMatrix);
    }

    // Reset flags after updating children
    if (transformComponent.Position.Changed)
    {
        transformComponent.Position.Changed = false;
    }

    if (transformComponent.Rotation.Changed)
    {
        transformComponent.Rotation.Changed = false;
    }

    if (transformComponent.Scale.Changed)
    {
        transformComponent.Scale.Changed = false;
    }
}

void Scene::Draw()
{
    auto view = m_Registry.view<std::shared_ptr<Model>, Transform, Parent, Children>();
    auto lights = m_Registry.view<Light, Transform>();

    auto numLightsInShader = std::min(lights.size_hint(), ShaderProgram::MAX_NUM_LIGHTS);

    std::array<ShaderLight, ShaderProgram::MAX_NUM_LIGHTS> selectedLights;

    // TODO: get closest/strongest lights first, up to max size shader supports
    // Currently just grabs first because it's easy
    auto it_lights = lights.begin();
    for (size_t i = 0; i < numLightsInShader; i++)
    {
        if (it_lights != lights.end())
        {
            auto &light = m_Registry.get<Light>(*it_lights);
            auto &pos = m_Registry.get<Transform>(*it_lights);

            selectedLights[i].pos = glm::vec4((glm::vec3)pos.Position, 1.0f);
            selectedLights[i].properties = light;

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
        if (view.get<Parent>(entity).Get() == entt::null)
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
    auto [identifierComponent, transformComponent, childrenComponent] =
        m_Registry.get<Identifier, Transform, Children>(entity);

    glm::vec3 position = transformComponent.Position;
    glm::vec3 rotation = transformComponent.Rotation;
    glm::vec3 scale = transformComponent.Scale;

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

    transformComponent.Position = position;
    transformComponent.Rotation = rotation;
    transformComponent.Scale = scale;
}
