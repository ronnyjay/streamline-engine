#pragma once

#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <filesystem>

namespace engine
{

struct model
{
    model(const std::string &path);

    std::vector<mesh> meshes;

    void draw(const std::shared_ptr<shader> &s);

  private:
    const std::filesystem::path path;

    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<std::shared_ptr<texture>> loadMaterialTextures(aiMaterial *material, aiTextureType type,
                                                               texture_type typeName);
};

} // namespace engine