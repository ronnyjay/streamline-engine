#include <engine/resource_manager/resource_manager.hpp>
#include <memory>

using namespace engine;

std::unique_ptr<resource_manager> resource_manager::m_instance = nullptr;

resource_manager &resource_manager::get_reference()
{
    if (m_instance == nullptr)
    {
        m_instance = std::unique_ptr<resource_manager>(new resource_manager);
    }

    return *m_instance;
}
