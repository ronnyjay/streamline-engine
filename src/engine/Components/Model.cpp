#include "engine/Components/Mesh.hpp"
#include <assimp/matrix4x4.h>
#include <engine/Components/Model.hpp>
#include <engine/Logger/Logger.hpp>
#include <engine/ResourceManager/ResourceManager.hpp>
#include <engine/stb/stb_image.hpp>

#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include <memory>

using namespace engine;

void Model::Load(const std::basic_string<char> &path)
{
    Logger::Info("Loading model: %s\n", path.c_str());
    m_Path = path;

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::Warn("Error loading model: %s\n", importer.GetErrorString());
    }

    ProcessNode(scene->mRootNode, scene);

    Logger::Info("Model loaded successfully.\n");
}

Model::~Model()
{
}

void Model::Draw(const ShaderProgram &shader)
{
    for (auto &mesh : m_Meshes)
    {
        mesh.Draw(shader);
    }
}

const std::vector<Mesh> &Model::GetMeshes() const
{
    return m_Meshes;
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // Node contains indices to index meshes
        // Scene contains all data
        m_Meshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
    }

    // Recursively process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // Process Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        Vector vector;

        SetVertexBoneDataToDefault(vertex);

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if (mesh->mTextureCoords[0])
        {
            vector.x = mesh->mTextureCoords[0][i].x;
            vector.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vector;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process Materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<std::shared_ptr<Texture>> diffuseMaps =
        LoadMaterialTextures(material, aiTextureType_DIFFUSE, "TexDiffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<std::shared_ptr<Texture>> specularMaps =
        LoadMaterialTextures(material, aiTextureType_SPECULAR, "TexSpecular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<std::shared_ptr<Texture>> normalMaps =
        LoadMaterialTextures(material, aiTextureType_HEIGHT, "TexNormal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<std::shared_ptr<Texture>> heightMaps =
        LoadMaterialTextures(material, aiTextureType_AMBIENT, "TexHeight");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    ExtractBoneWeightForVertices(vertices, mesh, scene);

    // Return a mesh object from extracted data
    return Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>>
Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < std::max(material->GetTextureCount(type), 1u); i++)
    {
        aiString path;
        aiString directory(m_Path.parent_path().c_str());

        if (material->GetTextureCount(type))
        {
            material->GetTexture(type, i, &path);
        }
        else
        {
            switch (type)
            {
            case aiTextureType_DIFFUSE:
                path = aiString("diffuse.jpg");
                break;
            case aiTextureType_SPECULAR:
                path = aiString("roughness.jpg");
                break;
            case aiTextureType_HEIGHT:
                path = aiString("normal.jpg");
                break;
            case aiTextureType_AMBIENT:
                path = aiString("ambient.jpg");
                break;
            default:
                break;
            }

            directory = aiString(ResourceManager::DEFAULT_TEXTURE_DIR);
        }

        // Check if texture has been previously loaded
        std::filesystem::path texturePath(directory.C_Str());
        texturePath.append(path.C_Str());

        auto texture = ResourceManager::GetReference().Get<Texture>(texturePath);
        texture->m_Type = typeName;
        textures.push_back(texture);
    }

    return textures;
}

void Model::SetVertexBoneData(Vertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.BoneIds[i] < 0)
        {
            vertex.Weights[i] = weight;
            vertex.BoneIds[i] = boneID;
            break;
        }
    }
}

void Model::SetVertexBoneDataToDefault(Vertex &vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        vertex.Weights[i] = -1;
        vertex.BoneIds[i] = 0.0f;
    }
}

void Model::ExtractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh *mesh, const aiScene *scene)
{
    for (uint boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = m_BoneCounter;
            newBoneInfo.offset = AssimpMat4ToGLMMat4(mesh->mBones[boneIndex]->mOffsetMatrix);

            m_BoneInfoMap[boneName] = newBoneInfo;
            boneID = m_BoneCounter;
            m_BoneCounter++;
        }
        else
        {
            boneID = m_BoneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            uint vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}
