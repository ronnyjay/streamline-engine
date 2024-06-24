#include <engine/resource_manager/resource_manager.hpp>
#include <memory>

using namespace engine;

std::unique_ptr<ResourceManager> ResourceManager::m_Instance = nullptr;

ResourceManager &ResourceManager::GetReference()
{
    if (m_Instance == nullptr)
    {
        m_Instance = std::unique_ptr<ResourceManager>(new ResourceManager);
    }

    return *m_Instance;
}
