#include <engine/entity/entity.hpp>

using namespace engine;

Entity::Entity(entt::entity handle, Scene *scene) : m_Handle(handle), m_Scene(scene)
{
}
