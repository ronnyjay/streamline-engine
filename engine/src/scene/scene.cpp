#include "scene/scene.hpp"

using namespace engine;

void scene::tick(double dt)
{
    m_playerInputSystem.update(dt);
    m_controllerSystem.update(dt);
    m_followSystem.update(dt);
    m_cameraSystem.update(dt);
}

void scene::draw()
{
    Camera *activeCamera = nullptr;

    auto    cameras = m_registry.view<Camera>();
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
}
