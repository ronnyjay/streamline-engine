
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
        : m_text(text), m_position(x, y), m_color(color), m_scale(scale), m_character_texture("resources/textures/characters16x16.bmp")
    {
        // clang-format off
        const GLfloat data[4][4] = {
            { -1.0f, -1.0f, 0.0f, 0.0f},
            { +1.0f, -1.0f, 0.0f, 0.0f},
            { -1.0f, +1.0f, 0.0f, 0.0f},
            { +1.0f, +1.0f, 0.0f, 0.0f},
        };
        // clang-format on

        Shader vertex_shader("resources/shaders/text/text.vs", GL_VERTEX_SHADER);
        Shader fragment_shader("resources/shaders/text/text.fs", GL_FRAGMENT_SHADER);

        m_shader_program.add_shader(vertex_shader.get_id());
        m_shader_program.add_shader(fragment_shader.get_id());
        m_shader_program.link();

        m_vao.bind();
        m_vbo.bind();
        m_vao.set(0, 2, GL_FLOAT, 7 * sizeof(float), (void *)0);                   // rectangle position
        m_vao.set(1, 2, GL_FLOAT, 7 * sizeof(float), (void *)(2 * sizeof(float))); // uv coordinates
        m_vao.set(2, 3, GL_FLOAT, 7 * sizeof(float), (void *)(4 * sizeof(float))); // color
        m_vbo.initialize(data, sizeof(data), GL_STATIC_DRAW);
        m_vao.unbind();
        m_vbo.unbind();
    }

    void draw();

  private:
    std::string m_text;

    glm::vec2 m_position;
    glm::vec3 m_color;

    float m_scale;
    float m_max_x;

    VBO m_vbo;
    VAO m_vao;

    ShaderProgram m_shader_program;
    Texture m_character_texture;
};

}; // namespace engine
