#pragma once

#include <engine/mesh/mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#define DEFAULT_TEXTURE_DIR "resources/textures/default"

namespace engine
{

typedef glm::vec3 Vector;

class Model
{
  public:
    Model(const std::string &path);

    void Draw(const Shader &);

    const std::vector<Mesh> &GetMeshes() const;

  private:
    std::string m_Directory;

    glm::vec3 m_Min;
    glm::vec3 m_Max;

    std::vector<Mesh> m_Meshes;
    std::vector<MaterialTexture> m_TexturesLoaded;

    void ProcessNode(aiNode *, const aiScene *);
    Mesh ProcessMesh(aiMesh *, const aiScene *);

    std::vector<MaterialTexture> LoadMaterialTextures(aiMaterial *, aiTextureType, std::string);
};

}; // namespace engine