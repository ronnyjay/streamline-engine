#include "renderer/model.hpp"

#include "subsystems/resource_manager.hpp"
#include <filesystem>

using namespace engine;

Model::Model(const std::string &path)
    : path(path)
{
    Assimp::Importer importer;

    const aiScene   *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                         aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        STREAMLINE_ASSERT(false, "Failed to load model");
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // Node contains indices to index meshes
        // Scene contains all data
        processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<vertex>                   vertices;
    std::vector<uint>                     indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertex vertex;
        vec3   vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.position = vector;

        if (mesh->HasNormals())
        {
            vector.x      = mesh->mNormals[i].x;
            vector.y      = mesh->mNormals[i].y;
            vector.z      = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if (mesh->mTextureCoords[0])
        {
            vector.x         = mesh->mTextureCoords[0][i].x;
            vector.y         = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vector.xy(); /// TODO: remove swizzle operator in favor of assignment to vec2

            vector.x       = mesh->mTangents[i].x;
            vector.y       = mesh->mTangents[i].y;
            vector.z       = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x         = mesh->mBitangents[i].x;
            vector.y         = mesh->mBitangents[i].y;
            vector.z         = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
        {
            vertex.texCoords = vec2(0.0f, 0.0f);
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
    aiMaterial                           *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<std::shared_ptr<Texture>> diffuseMaps =
        loadMaterialTextures(material, aiTextureType_DIFFUSE, texture_type::DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<std::shared_ptr<Texture>> specularMaps =
        loadMaterialTextures(material, aiTextureType_SPECULAR, texture_type::SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<std::shared_ptr<Texture>> normalMaps =
        loadMaterialTextures(material, aiTextureType_HEIGHT, texture_type::NORMAL);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<std::shared_ptr<Texture>> heightMaps =
        loadMaterialTextures(material, aiTextureType_AMBIENT, texture_type::HEIGHT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Return a mesh object from extracted data
    meshes.emplace_back(engine::mesh(vertices, indices, textures));
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type,
                                                                  texture_type typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < std::max(material->GetTextureCount(type), 1u); i++)
    {
        aiString path;
        aiString directory(this->path.parent_path().c_str());

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

            directory = aiString(ResourceManager::DEFAULT_TEXTURE_DIR.data());
        }

        std::filesystem::path texture_path = std::string(directory.C_Str());
        texture_path.append(path.C_Str());

        std::shared_ptr<Texture> t = ResourceManager::getInstance().getTexture(texture_path);
        t->type                    = typeName;

        textures.push_back(t);
    }

    return textures;
}

void Model::draw(const std::shared_ptr<Shader> &s)
{
    for (auto &mesh : meshes)
    {
        mesh.draw(s);
    }
}
