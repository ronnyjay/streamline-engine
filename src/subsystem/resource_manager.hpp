#pragma once

#include "core/logger.hpp"

#include <iostream> // IWYU pragma: keep
#include <map>      // IWYU pragma: keep
#include <string>   // IWYU pragma: keep

namespace engine
{

//
// Forward Declarations
//
class Model;
class Shader;
class Texture;

/**
 * @brief
 *
 */
struct Loadable
{
    /**
     * @brief
     *
     */
    virtual ~Loadable()
    {
    }

    /**
     * @brief
     *
     * @param path
     */
    virtual int Load(const std::string &path) = 0;
};

/**
 * @brief
 *
 */
class ResourceManager
{
  public:
    /**
     * @brief
     *
     */
    inline static const std::string DEFAULT_TEXTURE_DIR = "resources/textures/default";

    /**
     * @brief Loads and generates a texture from a specified filepath
     *
     * @param id The texture's unique identifier
     * @param path The path to the texture
     * @return Texture& The generated texture
     */
    static Texture &LoadTexture(std::string id, std::string path);

    /**
     * @brief Retrieves a stored texture
     *
     * @param id The texture's unique identifier
     * @return Texture& The stored texture
     */
    static Texture &GetTexture(std::string id);

    /**
     * @brief Loads and generates a shader from vertex and fragment shader files
     *
     * @param id The shader's unique identifier
     * @param vertex_path The path to the vertex shader's source
     * @param fragment_path The path to the fragment shader's source
     * @return Shader& The generated shader
     */
    static Shader &LoadShader(std::string id, std::string vertex_path, std::string fragment_path);

    /**
     * @brief Retrieves a stored shader
     *
     * @param id The shader's unique identifier
     * @return Shader& The stored shader
     */
    static Shader &GetShader(std::string id);

    /**
     * @brief Loads and generates a model from a specified filepath
     *
     * @param id The model's unique identifier
     * @param path The path to the model
     * @return Model& The generated model
     */
    static Model &LoadModel(std::string id, std::string path);

    /**
     * @brief Retrieves a stored model
     *
     * @param id The model's unique identifier
     * @return Model& The stored model
     */
    static Model &GetModel(std::string id);

  private:
    /**
     * @brief Default constructor
     *
     */
    ResourceManager()
    {
    }

    static Logger kLogger;

    // Loaded textures
    static std::map<std::string, Texture> kTextures;

    // Loaded shaders
    static std::map<std::string, Shader> kShaders;

    // Loaded models
    static std::map<std::string, Model> kModels;
};

} // namespace engine