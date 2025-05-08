#pragma once

#include "math/vec2.hpp" // IWYU pragma: keep
#include "math/vec3.hpp" // IWYU pragma: keep

#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include <memory>
#include <vector>

namespace engine
{

struct Vertex
{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 tangent;
    vec3 bitangent;
};

struct Mesh
{
    Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices,
         const std::vector<std::shared_ptr<Texture>> &textures);

    const std::vector<Vertex> &getVertices() const
    {
        return m_vertices;
    }

    void draw(const std::shared_ptr<Shader> &s);

  private:
    uint32_t                              m_VAO;
    uint32_t                              m_VBO;
    uint32_t                              m_EBO;

    std::vector<Vertex>                   m_vertices;
    std::vector<uint32_t>                 m_indices;

    std::vector<std::shared_ptr<Texture>> m_textures;
};

} // namespace engine