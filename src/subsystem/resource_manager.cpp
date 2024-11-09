#include <subsystem/resource_manager.hpp>

#include <renderer/model.hpp>
#include <renderer/shader.hpp>
#include <renderer/texture.hpp>

#include <core/exception.hpp>

using namespace engine;

Logger                         ResourceManager::kLogger(TYPENAME(ResourceManager));

std::map<std::string, Texture> ResourceManager::kTextures;
std::map<std::string, Shader>  ResourceManager::kShaders;
std::map<std::string, Model>   ResourceManager::kModels;

Model                         &ResourceManager::LoadModel(std::string id, std::string path)
{
    if (!kModels.contains(id))
    {
        if (kModels[id].Load(path) == 0)
        {
            kLogger.Info("ResourceManager - Loaded model: " + path);
        }
        else
        {
            kLogger.Warn("ResourceManager - Failed to load model: " + path);
        }
    }

    return kModels[id];
}

Model &ResourceManager::GetModel(std::string id)
{
    if (!kModels.contains(id))
    {
        throw MissingResourceException(id, std::source_location::current());
    }

    return kModels[id];
}

Shader &ResourceManager::LoadShader(std::string id, std::string vertex_path, std::string fragment_path)
{
    if (!kShaders.contains(id))
    {
        bool vertex = kShaders[id].add_shader(vertex_path, GL_VERTEX_SHADER);

        if (!vertex)
        {
            kLogger.Warn("ResourceManager - Failed to load vertex shader: " + vertex_path);
        }
        else
        {
            kLogger.Info("ResourceManager - Loaded vertex shader: " + vertex_path);
        }

        bool fragment = kShaders[id].add_shader(fragment_path, GL_FRAGMENT_SHADER);

        if (!fragment)
        {
            kLogger.Warn("ResourceManager - Failed to load fragment shader: " + fragment_path);
        }
        else
        {
            kLogger.Info("ResourceManager - Loaded fragment shader: " + fragment_path);
        }

        bool compile = kShaders[id].compile();

        if (!compile)
        {
            kLogger.Warn("Failed to load shader program: " + id);
        }
        else
        {
            kLogger.Info("Loaded shader program: " + id);
        }
    }

    return kShaders[id];
}

Shader &ResourceManager::GetShader(std::string id)
{
    if (!kShaders.contains(id))
    {
        throw MissingResourceException(id, std::source_location::current());
    }

    return kShaders[id];
}

Texture &ResourceManager::LoadTexture(std::string id, std::string path)
{
    if (!kTextures.contains(id))
    {
        if (kTextures[id].Load(path) == 0)
        {
            kLogger.Info("Loaded texture: " + path);
        }
        else
        {
            kLogger.Warn("Failed to load texture: " + path);
        }

        kTextures[id].Load(path);
    }

    return kTextures[id];
}

Texture &ResourceManager::GetTexture(std::string id)
{
    if (!kTextures.contains(id))
    {
        throw MissingResourceException(id, std::source_location::current());
    }

    return kTextures[id];
}
