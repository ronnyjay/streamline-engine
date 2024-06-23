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
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
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
            glm::vec3 initialPosition = transform.GetPosition();
            glm::vec3 initialVelocity = rigidBody.GetLinearVelocity();

            glm::vec3 acceleration = forceAccumulator.AccumulatedForces;

            glm::vec3 k1_p = initialVelocity;
            glm::vec3 k1_v = acceleration;

            glm::vec3 k2_p = initialVelocity + k1_v * (dt * 0.5f);
            glm::vec3 k2_v = acceleration;

            glm::vec3 k3_p = initialVelocity + k2_v * (dt * 0.5f);
            glm::vec3 k3_v = acceleration;

            glm::vec3 k4_p = initialVelocity + k3_v * (dt * 0.5f);
            glm::vec3 k4_v = acceleration;

            transform.SetPosition(initialPosition + (k1_p + 2.0f * (k2_p + k3_p) + k4_p) * (dt / 6.0f));
            rigidBody.SetLinearVelocity(initialVelocity + (k1_v + 2.0f * (k2_v + k3_v) + k4_v) * (dt / 6.0f));

            // Integrate angular components
            glm::vec3 initialAngularVelocity = rigidBody.GetAngularVelocity();
            glm::vec3 angularAcceleration = glm::vec3(0.0f);

            glm::vec3 k1_r = initialAngularVelocity;
            glm::vec3 k1_w = angularAcceleration;

            glm::vec3 k2_r = initialAngularVelocity + k1_w * (dt * 0.5f);
            glm::vec3 k2_w = angularAcceleration;

            glm::vec3 k3_r = initialAngularVelocity + k2_w * (dt * 0.5f);
            glm::vec3 k3_w = angularAcceleration;

            glm::vec3 k4_r = initialAngularVelocity + k3_w * (dt * 0.5f);
            glm::vec3 k4_w = angularAcceleration;

            transform.SetRotation(transform.GetRotation() + (initialAngularVelocity * dt));
            rigidBody.SetAngularVelocity(initialAngularVelocity + (k1_w + 2.0f * (k2_w + k3_w) + k4_w) * (dt / 6.0f));
            rigidBody.SetAngularVelocity(rigidBody.GetAngularVelocity() * 0.99f);

            forceAccumulator.AccumulatedForces = glm::vec3(0.0f);
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

        glm::vec3 difference = (centerB - centerA);
        glm::vec3 overlap = halfWidthA + halfWidthB - glm::abs(centerB - centerA);

        glm::vec3 collisionNormal;
        glm::vec3 collisionPosition;
        float collisionPenetration;

        if (overlap.x < overlap.y && overlap.x < overlap.z)
        {
            collisionNormal = glm::vec3(1.0f, 0.0f, 0.0f) * glm::sign(centerB.x - centerA.x);
            collisionPosition = glm::vec3(centerA.x + glm::sign(difference.x) * halfWidthA.x, centerB.y, centerB.z);
            collisionPenetration = overlap.x;
        }
        else if (overlap.y < overlap.x && overlap.y < overlap.z)
        {
            collisionNormal = glm::vec3(0.0f, 1.0f, 0.0f) * glm::sign(centerB.y - centerA.y);
            collisionPosition = glm::vec3(centerB.x, centerA.y + glm::sign(difference.y) * halfWidthA.y, centerB.z);
            collisionPenetration = overlap.y;
        }
        else
        {
            collisionNormal = glm::vec3(0.0f, 0.0f, 1.0f) * glm::sign(centerB.z - centerA.z);
            collisionPosition = glm::vec3(centerB.x, centerB.y, centerA.z + glm::sign(difference.z) * halfWidthA.z);
            collisionPenetration = overlap.z;
        }

        if (bodyA && bodyB)
        {
            float totalMass = bodyA->GetInverseMass() + bodyB->GetInverseMass();

            transformA.SetPosition(
                transformA.GetPosition() -
                collisionNormal * collisionPenetration * (bodyA->GetInverseMass() / totalMass));

            transformB.SetPosition(
                transformB.GetPosition() +
                collisionNormal * collisionPenetration * (bodyB->GetInverseMass() / totalMass));

            // glm::vec3 relativePositionA = collisionPosition - transformA.GetPosition();
            // glm::vec3 relativePositionB = collisionPosition - transformB.GetPosition();

            glm::vec3 relativeVelocityA = collisionPosition - transformA.GetPosition();
            glm::vec3 relativeVelocityB = collisionPosition - transformB.GetPosition();

            glm::vec3 angularVelocityA = glm::cross(bodyA->GetAngularVelocity(), relativeVelocityA);
            glm::vec3 angularVelocityB = glm::cross(bodyB->GetAngularVelocity(), relativeVelocityB);

            glm::vec3 fullVelocityA = bodyA->GetLinearVelocity() + angularVelocityA;
            glm::vec3 fullVelocityB = bodyB->GetLinearVelocity() + angularVelocityB;

            glm::vec3 contactVelocity = fullVelocityB - fullVelocityA;

            float impulseForce = glm::dot(contactVelocity, collisionNormal);

            glm::vec3 inertiaA = glm::cross(
                bodyA->GetInertiaTensor() * glm::cross(relativeVelocityA, collisionNormal), relativeVelocityA);

            glm::vec3 inertiaB = glm::cross(
                bodyB->GetInertiaTensor() * glm::cross(relativeVelocityB, collisionNormal), relativeVelocityB);

            float a = glm::dot(inertiaA + inertiaB, collisionNormal);
            float e = (bodyA->GetRestitution() + bodyB->GetRestitution()) * 0.5f;
            float j = (-(1.0f + e) * impulseForce) / (totalMass + a);

            glm::vec3 fullImpulse = collisionNormal * j;

            bodyA->ApplyLinearImpulse(-fullImpulse);
            bodyB->ApplyLinearImpulse(fullImpulse);

            bodyA->ApplyAngularImpulse(glm::cross(relativeVelocityA, -fullImpulse));
            bodyB->ApplyAngularImpulse(glm::cross(relativeVelocityB, fullImpulse));
        }
        else if (bodyB)
        {
            transformB.SetPosition(
                transformB.GetPosition() + collisionNormal * collisionPenetration * bodyB->GetInverseMass());

            float e = bodyB->GetRestitution();
            float j = (-(1.0f + e) * glm::dot(bodyB->GetLinearVelocity(), collisionNormal));

            glm::vec3 fullImpulse = collisionNormal * j;

            bodyB->ApplyLinearImpulse(fullImpulse);
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

    for (auto &child : childrenComponent.Get())
    {
        auto &childTransformComponent = m_Registry.get<Transform>(child);

        if (transformComponent.IsDirty())
        {
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

            selectedLights[i].pos = glm::vec4((glm::vec3)pos.GetPosition(), 1.0f);
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

    glm::vec3 position = transformComponent.GetPosition();
    glm::vec3 rotation = transformComponent.GetRotation();
    glm::vec3 scale = transformComponent.GetScale();

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
