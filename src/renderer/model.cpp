#include "model.hpp"

#include "core/logger.hpp"

#include <filesystem>

using namespace engine;

int Model::load(const std::string &path)
{
    m_path = path;

    Assimp::Importer importer;

    const aiScene   *scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        logger::warn("Error loading model: %s", importer.GetErrorString());

        return 1;
    }

    process_node(scene->mRootNode, scene);

    return 0;
}

void Model::process_node(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // Node contains indices to index meshes
        // Scene contains all data
        process_mesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    // Recursively process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

void Model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex>                          vertices;
    std::vector<unsigned int>                    indices;
    std::vector<std::reference_wrapper<Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex    vertex;
        glm::vec3 vector;

        vector.x        = mesh->mVertices[i].x;
        vector.y        = mesh->mVertices[i].y;
        vector.z        = mesh->mVertices[i].z;

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
            vertex.texCoords = vector;

            vector.x         = mesh->mTangents[i].x;
            vector.y         = mesh->mTangents[i].y;
            vector.z         = mesh->mTangents[i].z;
            vertex.tangent   = vector;

            vector.x         = mesh->mBitangents[i].x;
            vector.y         = mesh->mBitangents[i].y;
            vector.z         = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
        {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
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
    aiMaterial                                  *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<std::reference_wrapper<Texture>> diffuseMaps =
        load_material_textures(material, aiTextureType_DIFFUSE, "TexDiffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<std::reference_wrapper<Texture>> specularMaps =
        load_material_textures(material, aiTextureType_SPECULAR, "TexSpecular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<std::reference_wrapper<Texture>> normalMaps =
        load_material_textures(material, aiTextureType_HEIGHT, "TexNormal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<std::reference_wrapper<Texture>> heightMaps =
        load_material_textures(material, aiTextureType_AMBIENT, "TexHeight");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Return a mesh object from extracted data
    m_meshes.emplace_back(Mesh(vertices, indices, textures));
}

std::vector<std::reference_wrapper<Texture>>
Model::load_material_textures(aiMaterial *material, aiTextureType type, std::string type_name)
{
    std::vector<std::reference_wrapper<Texture>> textures;

    for (unsigned int i = 0; i < std::max(material->GetTextureCount(type), 1u); i++)
    {
        aiString path;
        aiString directory(m_path.parent_path().c_str());

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

        std::filesystem::path texture_path = std::string(directory.C_Str()) + "/" + path.C_Str();

        Texture              &texture      = ResourceManager::LoadTexture(texture_path, texture_path);
        texture.type                       = type_name;

        textures.push_back(texture);
        m_textures.push_back(texture);
    }

    return textures;
}
