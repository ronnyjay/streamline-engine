#include "resource_manager.hpp"

#include "renderer/model.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include "core/exception.hpp"
#include "core/logger.hpp"

using namespace engine;

std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, Shader>  ResourceManager::shaders;
std::map<std::string, Model>   ResourceManager::models;

//

Model &ResourceManager::load_model(std::string id, std::string path)
{
    if (!models.contains(id))
    {
        if (models[id].load(path) == 0)
        {
            logger::info("ResourceManager - Loaded model: " + path);
        }
        else
        {
            logger::warn("ResourceManager - Failed to load model: " + path);
        }
    }

    return models[id];
}

Model &ResourceManager::get_model(std::string id)
{
    if (!models.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return models[id];
}

Shader &ResourceManager::load_shader(std::string id, std::string vertex_path, std::string fragment_path)
{
    if (!shaders.contains(id))
    {
        bool vertex = shaders[id].add_shader(vertex_path, GL_VERTEX_SHADER);

        if (!vertex)
        {
            logger::warn("ResourceManager - Failed to load vertex shader: " + vertex_path);
        }
        else
        {
            logger::info("ResourceManager - Loaded vertex shader: " + vertex_path);
        }

        bool fragment = shaders[id].add_shader(fragment_path, GL_FRAGMENT_SHADER);

        if (!fragment)
        {
            logger::warn("ResourceManager - Failed to load fragment shader: " + fragment_path);
        }
        else
        {
            logger::info("ResourceManager - Loaded fragment shader: " + fragment_path);
        }

        bool compile = shaders[id].compile();

        if (!compile)
        {
            logger::warn("ResourceManager - Failed to load shader program: " + id);
        }
        else
        {
            logger::info("ResourceManager - Loaded shader program: " + id);
        }
    }

    return shaders[id];
}

Shader &ResourceManager::get_shader(std::string id)
{
    if (!shaders.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return shaders[id];
}

Texture &ResourceManager::load_texture(std::string id, std::string path)
{
    if (!textures.contains(id))
    {
        if (textures[id].load(path) == 0)
        {
            logger::info("ResourceManager - Loaded texture: " + path);
        }
        else
        {
            logger::warn("ResourceManager - Failed to load texture: " + path);
        }

        textures[id].load(path);
    }

    return textures[id];
}

Texture &ResourceManager::get_texture(std::string id)
{
    if (!textures.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return textures[id];
}
