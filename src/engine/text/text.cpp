
#include <engine/text/text.hpp>

using namespace engine;

void Text::draw(ShaderProgram &s)
{
    const float x_scale = 0.03f;
    const float y_scale = 0.1f;
    const float padding = 0.05f;

    const float char_width_pixels = (float)m_character_texture.m_width / 32; // image width / characters per line
    const float char_height_pixels = char_width_pixels;

    const float char_width_uv = char_width_pixels / m_character_texture.m_width;
    const float char_height_uv = char_height_pixels / m_character_texture.m_height;

    s.bind();

    m_vbo.bind();
    m_vao.bind();
    m_character_texture.bind();

    float x1 = m_pos.x;
    float y1 = m_pos.y;
    float y2 = y1 + y_scale * m_scale;

    for (const char c : m_text)
    {
        float x2 = x1 + x_scale * m_scale;
        if (c == '\n' || (x2 > m_max_x && c == ' '))
        {
            x1 = m_pos.x;
            y1 = y1 - y_scale * m_scale - padding;
            y2 = y1 + y_scale * m_scale;
            x2 = x1 + x_scale * m_scale;
            continue;
        }

        int texture_x = c % 32;
        int texture_y = c / 32;

        float u1 = texture_x * char_width_uv;
        float v1 = texture_y * char_height_uv;

        float u2 = u1 + char_width_uv;
        float v2 = v1 + char_height_uv;

        // clang-format off
        const GLfloat data[][7] = {
            { x1, y1, u1, v1, m_color.r, m_color.g, m_color.b },
            { x2, y1, u2, v1, m_color.r, m_color.g, m_color.b },
            { x1, y2, u1, v2, m_color.r, m_color.g, m_color.b },
            { x2, y2, u2, v2, m_color.r, m_color.g, m_color.b },
        };
        // const GLfloat data[4][4] = {
        //     { -0.3f, -0.3f, 0, 0},
        //     { +0.3f, -0.3f, 1, 0},
        //     { -0.3f, +0.3f, 0, 1},
        //     { +0.3f, +0.3f, 1, 1},
        // };
        // clang-format on

        m_vbo.initialize(data, sizeof(data), GL_STATIC_DRAW);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x1 = x2;
    }

    m_character_texture.unbind();

    m_vao.unbind();
    m_vbo.unbind();
}
