#include <engine/InputManager/InputManager.hpp>

using namespace engine;

std::unique_ptr<InputManager> InputManager::m_Instance = nullptr;

InputManager &InputManager::Instance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = std::unique_ptr<InputManager>(new InputManager);
    }

    return *m_Instance;
}