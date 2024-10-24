#include "input_manager.hpp"

using namespace engine;

std::unique_ptr<InputManager> InputManager::m_instance = nullptr;

InputManager                 &InputManager::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = std::unique_ptr<InputManager>(new InputManager);
    }

    return *m_instance;
}