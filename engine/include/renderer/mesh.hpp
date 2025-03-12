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
    mesh(const std::vector<vertex> &vertices, const std::vector<uint> &indices,
         const std::vector<std::shared_ptr<texture>> &textures);

    std::vector<vertex>                   vertices;
    std::vector<uint>                     indices;
    std::vector<std::shared_ptr<texture>> textures;

    void draw(const std::shared_ptr<shader> &s);

  private:
    uint vao;
    uint vbo;
    uint ebo;
};

} // namespace engine