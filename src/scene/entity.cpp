#include "entity.hpp"

using namespace engine;

Entity::Entity(entt::entity handle, Scene *scene)
    : m_handle(handle)
    , m_scene(scene)
{
}

bool Entity::operator==(const Entity &other) const
{
    return m_handle == other.m_handle && m_scene == other.m_scene;
}

bool Entity::operator!=(const Entity &other) const
{
    return (this != &other);
}