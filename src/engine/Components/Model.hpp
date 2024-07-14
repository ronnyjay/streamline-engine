#pragma once

#include <engine/Components/Bone.hpp>
#include <engine/Components/Mesh.hpp>
#include <engine/ResourceManager/ResourceManager.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <filesystem>
#include <string>

namespace engine
{

typedef glm::vec3 Vector;

inline glm::mat4 AssimpMat4ToGLMMat4(const aiMatrix4x4 &input)
{
    return glm::mat4(
        input.a1,
        input.b1,
        input.c1,
        input.d1,
        input.a2,
        input.b2,
        input.c2,
        input.d2,
        input.a3,
        input.b3,
        input.c3,
        input.d3,
        input.a4,
        input.b4,
        input.c4,
        input.d4);
}

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

    auto &GetBoneInfoMap()
    {
        return m_BoneInfoMap;
    }
    int &GetBoneCount()
    {
        return m_BoneCounter;
    }

  private:
    std::filesystem::path m_Path;

    std::vector<Mesh> m_Meshes;
    std::vector<std::shared_ptr<Texture>> m_TexturesLoaded;
    std::unordered_map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;
    void SetVertexBoneDataToDefault(Vertex &vertex);
    void SetVertexBoneData(Vertex &vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh *mesh, const aiScene *scene);

    void ProcessNode(aiNode *, const aiScene *);
    Mesh ProcessMesh(aiMesh *, const aiScene *);

    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial *, aiTextureType, std::string);
};

} // namespace engine
