#include "scene/scene.hpp"
#include "core/renderer.hpp"
#include "scene/components/transform.hpp"
#include <assimp/types.h>

using namespace engine;

void Scene::tick(double dt)
{
    m_playerInputSystem.update(dt);
    m_controllerSystem.update(dt);
    m_collisionSystem.update(dt);
    m_followSystem.update(dt);
    m_cameraSystem.update(dt);
}

void Scene::draw()
{
    Renderer::getInstance().beginFrame();

    Camera *activeCamera = nullptr;

    auto    cameras      = m_registry.view<Camera>();
    for (const auto &entity : cameras)
    {
        auto &camera = cameras.get(entity);

        if (camera.b_isPrimary)
        {
            activeCamera = &camera;
        }
    }

    STREAMLINE_ASSERT(activeCamera != nullptr, "No primary camera found, perhaps try creating one...");

    auto renderables = m_registry.view<Renderable, Transform>();

    for (const auto &entity : renderables)
    {
        auto [renderable, transform] = renderables.get(entity);

        m_shader.get()->bind();

        m_shader.get()->setMat4("projection", activeCamera->getProjectionMatrix());
        m_shader.get()->setMat4("view", activeCamera->getViewMatrix());

        m_shader.get()->setMat4("model", transform.getTransform());

        renderable.model.get()->draw(m_shader);
    }

    if (Renderer::getInstance().flags.b_showCollisions)
    {
        auto colliders = m_registry.view<AABB, Transform>();

        for (const auto &entity : colliders)
        {
            auto [collider, transform] = colliders.get(entity);

            m_aabbShader.get()->bind();

            m_aabbShader.get()->setMat4("projection", activeCamera->getProjectionMatrix());
            m_aabbShader.get()->setMat4("view", activeCamera->getViewMatrix());

            collider.draw();
        }
    }

    Renderer::getInstance().endFrame();
}
