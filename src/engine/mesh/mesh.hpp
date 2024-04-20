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
    mesh_t() : m_position(0.0f, 0.0f, 0.0f), m_matrix_model(glm::mat4(1.0f))
    {
    }

    virtual void update(double dt) = 0;
    virtual void draw(glm::mat4 projection, glm::mat4 view) = 0;

    void set_position(float x, float y, float z)
    {
        m_position = glm::vec3(x, y, z);
    }

    glm::vec3 const get_position() const
    {
        return m_position;
    }

  protected:
    glm::vec3 m_position;

    VAO m_vao;
    VBO m_vbo;

    glm::mat4 m_matrix_model;
    shader_program m_shader_program;
};

}; // namespace mesh

}; // namespace engine