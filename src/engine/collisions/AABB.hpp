#pragma once

#include <engine/renderer/EBO/EBO.hpp>
#include <engine/renderer/VAO/VAO.hpp>
#include <engine/renderer/VBO/VBO.hpp>
#include <engine/shader/shader.hpp>

#include <vector>

typedef glm::vec3 Vertex;
typedef unsigned int Index;
typedef std::array<float, 8> Point;

namespace engine
{

class AABB
{
  public:
    AABB();

    void initialize(const std::vector<Vertex> &vertices);

    void update(const std::vector<Point> &points, const glm::mat4 &model);
    void draw(const glm::mat4 &view, const glm::mat4 &projection);

    void check_collision(const glm::vec3 &);

    void set_colliding(bool value)
    {
        m_colliding = value;
    }

    Vertex const &min() const;
    Vertex const &max() const;

  private:
    Vertex m_min;
    Vertex m_max;

    bool m_colliding;

    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;

    ShaderProgram m_shader_program;
};

}; // namespace engine