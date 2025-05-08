#include "renderer/mesh.hpp"

using namespace engine;

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<std::shared_ptr<Texture>> &textures)
    : m_vertices(vertices)
    , m_indices(indices)
    , m_textures(textures)
{

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    // Vertex TexCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangent));

    // Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

void Mesh::draw(const std::shared_ptr<Shader> &s)
{
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    std::string  texNumber;
    std::string  texType;

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i]->bind(i);

        switch (m_textures[i]->type)
        {
        default:
        case texture_type::DIFFUSE:
            texType   = "TexDiffuse";
            texNumber = std::to_string(diffuseNr++);
            break;
        case texture_type::SPECULAR:
            texType   = "TexSpecular";
            texNumber = std::to_string(specularNr++);
            break;
        case texture_type::NORMAL:
            texType   = "TexNormal";
            texNumber = std::to_string(normalNr++);
            break;
        case texture_type::HEIGHT:
            texType   = "TexHeight";
            texNumber = std::to_string(heightNr++);
            break;
        }

        s->setInt(texType + texNumber, i);
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}