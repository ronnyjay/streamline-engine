#include "renderer/mesh.hpp"

using namespace engine;

mesh::mesh(const std::vector<vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<std::shared_ptr<Texture>> &textures)
    : vertices(vertices)
    , indices(indices)
    , textures(textures)
{

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, normal));

    // Vertex TexCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, texCoords));

    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, tangent));

    // Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, bitangent));

    glBindVertexArray(0);
}

void mesh::draw(const std::shared_ptr<Shader> &s)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    std::string texNumber;
    std::string texType;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i]->bind(i);

        switch (textures[i]->type)
        {
        default:
        case texture_type::DIFFUSE:
            texType = "TexDiffuse";
            texNumber = std::to_string(diffuseNr++);
            break;
        case texture_type::SPECULAR:
            texType = "TexSpecular";
            texNumber = std::to_string(specularNr++);
            break;
        case texture_type::NORMAL:
            texType = "TexNormal";
            texNumber = std::to_string(normalNr++);
            break;
        case texture_type::HEIGHT:
            texType = "TexHeight";
            texNumber = std::to_string(heightNr++);
            break;
        }

        s->setInt(texType + texNumber, i);
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}