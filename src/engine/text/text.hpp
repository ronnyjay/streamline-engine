
#pragma once

#include "engine/renderer/VAO/VAO.hpp"
#include "engine/renderer/VBO/VBO.hpp"
#include "engine/shader/shader.hpp"
#include "engine/texture/texture.hpp"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>

namespace engine
{

enum SpecialCharacter
{
    NullChar = 0,
    Heart,
};

class Text
{
  public:
    Text(const std::basic_string<char> &text, float x, float y, float scale, glm::vec3 color, float max_x)
        : m_character_texture("resources/textures/characters16x16.bmp"), m_text(text), m_pos(x, y), m_scale(scale), m_color(color)
    {
        // clang-format off
        const GLfloat data[4][4] = {
            { -1.0f, -1.0f, 0.0f, 0.0f},
            { +1.0f, -1.0f, 0.0f, 0.0f},
            { -1.0f, +1.0f, 0.0f, 0.0f},
            { +1.0f, +1.0f, 0.0f, 0.0f},
        };
        // clang-format on

        m_vao.bind();
        m_vbo.bind();

        // position data for rectangle
        m_vao.set(0, 2, GL_FLOAT, 7 * sizeof(float), (void *)0);

        // uv coordinates
        m_vao.set(1, 2, GL_FLOAT, 7 * sizeof(float), (void *)(2 * sizeof(float)));

        // color
        m_vao.set(2, 3, GL_FLOAT, 7 * sizeof(float), (void *)(4 * sizeof(float)));

        m_vbo.initialize(data, sizeof(data), GL_STATIC_DRAW);

        m_vao.unbind();
        m_vbo.unbind();
    }

    void draw(ShaderProgram &s);

  private:
    Texture m_character_texture;

    std::string m_text;
    glm::vec2 m_pos;
    float m_scale;
    glm::vec3 m_color;
    float m_max_x;

    VBO m_vbo;
    VAO m_vao;
};

}; // namespace engine