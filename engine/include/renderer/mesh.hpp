#pragma once

#include "math/vec2.hpp" // IWYU pragma: keep
#include "math/vec3.hpp" // IWYU pragma: keep

#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include <memory>
#include <vector>

namespace engine
{

struct vertex
{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 tangent;
    vec3 bitangent;
};

struct mesh
{
    mesh(const std::vector<vertex> &vertices, const std::vector<uint32_t> &indices,
         const std::vector<std::shared_ptr<Texture>> &textures);

    std::vector<vertex>                   vertices;
    std::vector<unsigned int>             indices;
    std::vector<std::shared_ptr<Texture>> textures;

    void                                  draw(const std::shared_ptr<Shader> &s);

  private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

} // namespace engine