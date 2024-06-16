#include <engine/text/text.hpp>

using namespace engine;

void Text::Draw()
{
    const float scaleX = 0.03f;
    const float scaleY = 0.1f;
    const float padding = 0.05f;

    const float charWidthPixels = (float)m_Texture->m_Width / 32; // image width / characters per line
    const float charHeightPixels = charWidthPixels;

    const float charWidthUV = charWidthPixels / m_Texture->m_Width;
    const float charHeightUV = charHeightPixels / m_Texture->m_Height;

    float x1 = m_Position.x;
    float y1 = m_Position.y;
    float y2 = y1 + scaleY * m_Scale;

    m_Shader.Use();

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    m_Texture->Bind();

    for (const char c : m_Text)
    {
        float x2 = x1 + scaleX * m_Scale;
        if (c == '\n' || (x2 > m_MaxX && c == ' '))
        {
            x1 = m_Position.x;
            y1 = y1 - scaleY * m_Scale - padding;
            y2 = y1 + scaleY * m_Scale;
            x2 = x1 + scaleX * m_Scale;
            continue;
        }

        int texture_x = c % 32;
        int texture_y = c / 32;

        float u1 = texture_x * charWidthUV;
        float v1 = texture_y * charHeightUV;

        float u2 = u1 + charWidthUV;
        float v2 = v1 + charHeightUV;

        // clang-format off
        const GLfloat data[][7] = {
            { x1, y1, u1, v1, m_Color.r, m_Color.g, m_Color.b },
            { x2, y1, u2, v1, m_Color.r, m_Color.g, m_Color.b },
            { x1, y2, u1, v2, m_Color.r, m_Color.g, m_Color.b },
            { x2, y2, u2, v2, m_Color.r, m_Color.g, m_Color.b },
        };
        // clang-format on

        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glEnable(GL_DEPTH_TEST);

        x1 = x2;
    }

    glBindVertexArray(0);
}