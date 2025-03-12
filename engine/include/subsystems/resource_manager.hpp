#pragma once

#include <map>
#include <string>
#include <string_view>

#include "core/singleton.hpp"

#include "renderer/model.hpp"   // IWYU pragma: keep
#include "renderer/shader.hpp"  // IWYU pragma: keep
#include "renderer/texture.hpp" // IWYU pragma: keep

namespace engine
{

struct resource_manager : public singleton<resource_manager>
{
    inline static const std::string_view DEFAULT_TEXTURE_DIR = "../assets/textures/default";

    std::shared_ptr<shader> getShader(const std::string id)
    {
        auto [it, insert] = shaders.emplace(id, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<shader>();

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<shader>(it->second);
    }

    std::shared_ptr<model> getModel(const std::string &path)
    {
        auto [it, insert] = models.emplace(path, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<model>(path);

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<model>(it->second);
    }

    std::shared_ptr<texture> getTexture(const std::string &path)
    {
        auto [it, insert] = textures.emplace(path, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<texture>(path);

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<texture>(it->second);
    }

  private:
    std::map<std::string, std::shared_ptr<shader>>  shaders;
    std::map<std::string, std::shared_ptr<model>>   models;
    std::map<std::string, std::shared_ptr<texture>> textures;
};

} // namespace engine