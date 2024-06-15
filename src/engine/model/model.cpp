#include <engine/logger/logger.hpp>
#include <engine/model/model.hpp>
#include <engine/stb/stb_image.hpp>

using namespace engine;

Model::Model(const std::string &path)
{
    Logger::info("Loading model: %s\n", path.c_str());

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::warn("Error loading model: %s\n", importer.GetErrorString());
    }

    m_Directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);

    Logger::info("Model loaded successfully.\n");
}

void Model::Draw(const Shader &shader)
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
    std::vector<MaterialTexture> textures;

    // Process Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        Vector vector;

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

    std::vector<MaterialTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "TexDiffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<MaterialTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "TexSpecular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<MaterialTexture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "TexNormal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<MaterialTexture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "TexHeight");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Return a mesh object from extracted data
    return Mesh(vertices, indices, textures);
}

std::vector<MaterialTexture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName)
{
    std::vector<MaterialTexture> textures;

    for (unsigned int i = 0; i < std::max(material->GetTextureCount(type), 1u); i++)
    {
        aiString path;
        aiString directory(m_Directory);

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

            directory = aiString(DEFAULT_TEXTURE_DIR);
        }

        // Check if texture has been previously loaded
        bool skip = false;

        for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++)
        {
            if (std::strcmp(m_TexturesLoaded[j].m_Path.data(), path.C_Str()) == 0)
            {
                textures.push_back(m_TexturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            MaterialTexture texture;

            texture = MaterialTexture::FromFile(path.C_Str(), directory.C_Str());
            texture.m_Type = typeName;

            textures.push_back(texture);
            m_TexturesLoaded.push_back(texture);
        }
    }

    return textures;
}