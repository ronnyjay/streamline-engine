#pragma once

#include <engine/shader/shader.hpp>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>
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

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
  public:
    Mesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>);

    void Draw(Shader &);

    const std::vector<Vertex> &GetVertices() const;

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
};

}; // namespace engine