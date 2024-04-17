#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <engine/VAO/VAO.hpp>
#include <engine/VBO/VBO.hpp>

#include <engine/shader/shader.hpp>
#include <engine/shader_program/shader_program.hpp>

namespace engine
{

namespace mesh
{

class mesh_t
{
  public:
    mesh_t() : m_matrix_model(glm::mat4(1.0f))
    {
    }

    virtual void update(double dt) = 0;
    virtual void draw(glm::mat4 projection, glm::mat4 view) = 0;

  protected:
    VAO m_vao;
    VBO m_vbo;

    glm::mat4 m_matrix_model;
    shader_program m_shader_program;
};

}; // namespace mesh

}; // namespace engine