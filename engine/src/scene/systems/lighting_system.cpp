#include "scene/scene.hpp"

using namespace engine;

void LightingSystem::update(double dt)
{
    auto view = m_scene->m_registry.view<Light, Transform>();

    for (const auto &entity : view)
    {
        auto [light, transform] = view.get(entity);
    }
}