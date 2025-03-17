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

struct ResourceManager : public Singleton<ResourceManager>
{
    inline static const std::string_view DEFAULT_TEXTURE_DIR = "../assets/textures/default";

    std::shared_ptr<Shader> getShader(const std::string &id, const std::string &vPath, const std::string &fPath)
    {
        auto [it, insert] = shaders.emplace(id, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<Shader>(vPath, fPath);

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<Shader>(it->second);
    }

    std::shared_ptr<Model> getModel(const std::string &path)
    {
        auto [it, insert] = models.emplace(path, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<Model>(path);

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<Model>(it->second);
    }

    std::shared_ptr<Texture> getTexture(const std::string &path)
    {
        auto [it, insert] = textures.emplace(path, nullptr);

        if (insert)
        {
            auto loadable = std::make_shared<Texture>(path);

            it->second = loadable;
        }

        return std::dynamic_pointer_cast<Texture>(it->second);
    }

  private:
    std::map<std::string, std::shared_ptr<Shader>>  shaders;
    std::map<std::string, std::shared_ptr<Model>>   models;
    std::map<std::string, std::shared_ptr<Texture>> textures;
};

} // namespace engine