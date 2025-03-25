#include "scene/systems/camera_system.hpp"
#include "core/logger.hpp"
#include "scene/scene.hpp"

#include <cstdint>

using namespace engine;

void CameraSystem::update(double dt)
{
    updateProjections();
    updateViews();
}

void CameraSystem::updateProjections()
{
    auto view = m_scene->m_registry.view<Camera>();

    for (const auto &entity : view)
    {
        auto &camera = view.get(entity);

        switch (camera.m_projection)
        {
        case Projection::Perspective:
        {
            camera.m_projectionMatrix =
                perspective(radians(camera.m_perspZoom), camera.m_aspectRatio, camera.m_perspNear, camera.m_perspFar);
        }
        break;
        case Projection::Orthographic:
        {
            camera.m_projectionMatrix =
                ortho(-(camera.m_aspectRatio * camera.m_orthoZoom), (camera.m_aspectRatio * camera.m_orthoZoom),
                      camera.m_orthoZoom, camera.m_orthoZoom, camera.m_orthoNear, camera.m_orthoFar);
        }
        break;
        }
    }
}

void CameraSystem::updateViews()
{
    auto view = m_scene->m_registry.view<Camera, Transform>();

    for (const auto &entity : view)
    {
        auto [camera, transform] = view.get(entity);

        switch (camera.m_projection)
        {
        case Projection::Perspective:
        {
            camera.m_viewMatrix =
                lookAt(transform.translation, transform.translation + transform.getFront(), transform.getUp());
        }
        break;
        case Projection::Orthographic:
        {
            camera.m_viewMatrix = mat4(1.0f);
            camera.m_viewMatrix = translate(camera.m_viewMatrix, transform.translation);
            camera.m_viewMatrix = rotate(camera.m_viewMatrix, radians(transform.rotation.y), vec3(0.0f, 1.0f, 0.0f));
            camera.m_viewMatrix = rotate(camera.m_viewMatrix, radians(transform.rotation.x), vec3(1.0f, 0.0f, 0.0f));
            camera.m_viewMatrix = inverse(camera.m_viewMatrix);
        }
        break;
        }
    }
}

void CameraSystem::updateAspectRatios(uint32_t width, uint32_t height)
{
    auto view = m_scene->m_registry.view<Camera>();

    for (const auto &entity : view)
    {
        auto &camera = view.get(entity);

        if (!camera.b_lockAspectRatio)
        {
            camera.setAspectRatio(width, height);
        }
    }

    updateProjections();
    updateViews();

    auto transform_view = m_scene->m_registry.view<Camera, Transform>();

    for (const auto &entity : transform_view)
    {
        auto [camera, transform] = transform_view.get(entity);

        Logger::info("Yaw: %.2f", transform.rotation.y);
    }
}