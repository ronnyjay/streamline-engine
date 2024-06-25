#pragma once

#include <engine/Components/Mesh.hpp>
#include <engine/ResourceManager/ResourceManager.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <filesystem>

namespace engine
{

typedef glm::vec3 Vector;

class Model : public Loadable
{
  public:
    Model()
    {
    }

    ~Model();

    void Draw(const ShaderProgram &);

    const std::vector<Mesh> &GetMeshes() const;
    void Load(const std::basic_string<char> &path) override;

  private:
    std::filesystem::path m_Path;

    std::vector<Mesh> m_Meshes;
    std::vector<std::shared_ptr<Texture>> m_TexturesLoaded;

    void ProcessNode(aiNode *, const aiScene *);
    Mesh ProcessMesh(aiMesh *, const aiScene *);

    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial *, aiTextureType, std::string);
};

}; // namespace engine
