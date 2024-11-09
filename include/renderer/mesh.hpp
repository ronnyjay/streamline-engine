#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include <vector>

namespace engine
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;

    glm::vec2 texCoords;

    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh
{
  public:
    Mesh(
        const std::vector<Vertex> &, const std::vector<unsigned int> &,
        const std::vector<std::reference_wrapper<Texture>> &);

    void draw(const Shader &);

  private:
    unsigned int                                 m_vao;
    unsigned int                                 m_vbo;
    unsigned int                                 m_ebo;

    std::vector<Vertex>                          m_vertices;
    std::vector<unsigned int>                    m_indices;
    std::vector<std::reference_wrapper<Texture>> m_textures;
};

} // namespace engine