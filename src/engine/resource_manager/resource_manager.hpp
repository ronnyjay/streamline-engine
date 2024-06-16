#pragma once

#include <engine/mesh/mesh.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace engine
{

class resource_manager
{
  public:
    static resource_manager &get_reference();

    template <typename T> std::shared_ptr<T> Get(const std::basic_string<char> &path)
    {
        auto it = m_Loadables.find(path);
        if (it == m_Loadables.cend())
        {
            std::shared_ptr<T> l = std::make_shared<T>();
            l->Load(path);
            it = m_Loadables.emplace(path, l).first;
        }
        
        return std::dynamic_pointer_cast<T>(it->second);
    }

    inline static const std::string DEFAULT_TEXTURE_DIR = "resources/textures/default";

  private:
    static std::unique_ptr<resource_manager> m_instance;

    std::unordered_map<std::string, std::shared_ptr<Loadable>> m_Loadables;

    resource_manager()
    {
    }
};

} // namespace engine
