#pragma once

#include <engine/mesh/mesh.hpp>
#include <engine/renderer/VAO/VAO.hpp>
#include <engine/renderer/VBO/VBO.hpp>
#include <engine/shader/shader.hpp>

namespace engine
{

class PyramidMesh : public Mesh
{
  public:
    PyramidMesh(const std::string &);

    virtual void update(double);
    virtual void draw(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &);

  private:
    VAO m_VAO;
    VBO m_VBO;
    ShaderProgram m_shader_program;
    static const GLfloat m_vertices[][5];
};

}; // namespace engine