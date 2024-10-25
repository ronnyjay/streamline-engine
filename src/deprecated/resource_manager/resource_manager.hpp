#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace engine
{

struct loadable
{
    virtual ~loadable()
    {
    }

    const std::string m_Path;

    virtual void load(const std::basic_string<char> &path) = 0;
};

/*
  TODO: consider making non-singleton
*/
class resource_manager
{
  public:
    static resource_manager &get_reference();

    template <typename T> std::shared_ptr<T> get(const std::basic_string<char> &path)
    {
        auto it = m_loadables.find(path);
        if (it == m_loadables.cend())
        {
            std::shared_ptr<T> l = std::make_shared<T>();
            l->load(path);
            it = m_loadables.emplace(path, l).first;
        }

        return std::dynamic_pointer_cast<T>(it->second);
    }

    inline static const std::string DEFAULT_TEXTURE_DIR = "resources/textures/default";

  private:
    resource_manager()
    {
    }

    std::unordered_map<std::string, std::shared_ptr<loadable>> m_loadables;

    static std::unique_ptr<resource_manager> m_ref;
};

} // namespace engine
