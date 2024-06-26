#pragma once

#include <engine/ResourceManager/ResourceManager.hpp>
#include <engine/Shader/Shader.hpp>
#include <engine/Texture/Texture.hpp>

namespace engine
{

class Text
{
  public:
    Text(
        const std::string &text,
        const float posX,
        const float posY,
        const float scale,
        const float maxX,
        const glm::vec3 color)
        : m_Text(text)
        , m_Position(posX, posY)
        , m_Color(color)
        , m_Scale(scale)
        , m_MaxX(maxX)
    {
        m_Shader.AddShader("resources/shaders/text.vs", GL_VERTEX_SHADER);
        m_Shader.AddShader("resources/shaders/text.fs", GL_FRAGMENT_SHADER);

        m_Texture = ResourceManager::GetReference().Get<Texture>("resources/textures/text/characters16x16.bmp");

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

    ShaderProgram m_Shader;
    std::shared_ptr<Texture> m_Texture;
};

} // namespace engine