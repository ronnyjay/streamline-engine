#pragma once

#include <engine/shader/shader.hpp>
#include <engine/texture/texture.hpp>

namespace engine
{

class Text
{
  public:
    Text(const std::string &text, float posX, float posY, float scale, float maxX, glm::vec3 color)
        : m_Text(text), m_Position(posX, posY), m_Color(color), m_Scale(scale), m_MaxX(maxX)
    {
        m_Shader = Shader::FromFile("resources/shaders/text.vs", "resources/shaders/text.fs");
        m_Texture = Texture::FromFile("resources/textures/text/characters16x16.bmp");

        // clang-format off
        const GLfloat data[4][4] = {
            { -1.0f, -1.0f, 0.0f, 0.0f},
            { +1.0f, -1.0f, 0.0f, 0.0f},
            { -1.0f, +1.0f, 0.0f, 0.0f},
            { +1.0f, +1.0f, 0.0f, 0.0f},
        };
        // clang-format on

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(4 * sizeof(float)));
    }

    void Draw();

  private:
    std::string m_Text;

    glm::vec2 m_Position;
    glm::vec3 m_Color;

    float m_Scale;
    float m_MaxX;

    unsigned int m_VAO;
    unsigned int m_VBO;

    Shader m_Shader;
    Texture m_Texture;
};

}; // namespace engine