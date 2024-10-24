#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include "core/resource_manager.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <filesystem>

namespace engine
{

class Model : public Loadable
{
  public:
    Model()
    {
    }

    void draw(const Shader &shader)
    {
        for (auto &mesh : m_meshes)
        {
            mesh.draw(shader);
        }
    }

    int                  load(const std::string &) override;

    std::vector<Mesh>    m_meshes;
    std::vector<Texture> m_textures;

  private:
    std::filesystem::path                        m_path;

    void                                         process_node(aiNode *, const aiScene *);
    void                                         process_mesh(aiMesh *, const aiScene *);

    std::vector<std::reference_wrapper<Texture>> load_material_textures(aiMaterial *, aiTextureType, std::string);
};

} // namespace engine