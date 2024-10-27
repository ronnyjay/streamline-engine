#include "resource_manager.hpp"

#include "renderer/model.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include "core/exception.hpp"
#include "core/logger.hpp"

using namespace engine;

std::map<std::string, Texture> ResourceManager::mTextures;
std::map<std::string, Shader>  ResourceManager::mShaders;
std::map<std::string, Model>   ResourceManager::mModels;

//

Model &ResourceManager::LoadModel(std::string id, std::string path)
{
    if (!mModels.contains(id))
    {
        if (mModels[id].load(path) == 0)
        {
            logger::info("ResourceManager - Loaded model: " + path);
        }
        else
        {
            logger::warn("ResourceManager - Failed to load model: " + path);
        }
    }

    return mModels[id];
}

Model &ResourceManager::GetModel(std::string id)
{
    if (!mModels.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return mModels[id];
}

Shader &ResourceManager::LoadShader(std::string id, std::string vertex_path, std::string fragment_path)
{
    if (!mShaders.contains(id))
    {
        bool vertex = mShaders[id].add_shader(vertex_path, GL_VERTEX_SHADER);

        if (!vertex)
        {
            logger::warn("ResourceManager - Failed to load vertex shader: " + vertex_path);
        }
        else
        {
            logger::info("ResourceManager - Loaded vertex shader: " + vertex_path);
        }

        bool fragment = mShaders[id].add_shader(fragment_path, GL_FRAGMENT_SHADER);

        if (!fragment)
        {
            logger::warn("ResourceManager - Failed to load fragment shader: " + fragment_path);
        }
        else
        {
            logger::info("ResourceManager - Loaded fragment shader: " + fragment_path);
        }

        bool compile = mShaders[id].compile();

        if (!compile)
        {
            logger::warn("ResourceManager - Failed to load shader program: " + id);
        }
        else
        {
            logger::info("ResourceManager - Loaded shader program: " + id);
        }
    }

    return mShaders[id];
}

Shader &ResourceManager::GetShader(std::string id)
{
    if (!mShaders.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return mShaders[id];
}

Texture &ResourceManager::LoadTexture(std::string id, std::string path)
{
    if (!mTextures.contains(id))
    {
        if (mTextures[id].load(path) == 0)
        {
            logger::info("ResourceManager - Loaded texture: " + path);
        }
        else
        {
            logger::warn("ResourceManager - Failed to load texture: " + path);
        }

        mTextures[id].load(path);
    }

    return mTextures[id];
}

Texture &ResourceManager::GetTexture(std::string id)
{
    if (!mTextures.contains(id))
    {
        throw missing_resource_exception(id, std::source_location::current());
    }

    return mTextures[id];
}
