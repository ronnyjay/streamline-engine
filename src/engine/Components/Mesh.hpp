#pragma once

#include <engine/Shader/Shader.hpp>
#include <engine/Texture/Texture.hpp>

#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>

#include <vector>

namespace engine
{

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int BoneIds[MAX_BONE_INFLUENCE];
    float Weights[MAX_BONE_INFLUENCE];
};

class Mesh
{
  public:
    Mesh(const std::vector<Vertex> &, const std::vector<unsigned int> &, const std::vector<std::shared_ptr<Texture>> &);

    void Draw(const ShaderProgram &);

    const std::vector<Vertex> &GetVertices() const;

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<std::shared_ptr<Texture>> m_Textures;
};

} // namespace engine
