#include "engine/mesh/mesh.hpp"
#include <engine/mesh/pyramid/pyramid.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

using namespace engine;

// clang-format off

const GLfloat PyramidMesh::m_vertices[][5] = {
// front face               
{-1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 1.0f, 1.0f, 0.f},
{0.0f, 2.0f, 0.0f, 0.5f, 1.0f},

// back face
{-1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
{1.0f, 0.0f, -1.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 0.0f, 0.5f, 1.0f},

// left face
{-1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
{-1.0f, 0.0f, -1.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 0.0f, 0.5f, 1.0f},

// right face
{1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 0.0f, 0.5f, 1.0f},

// bottom left face           
{1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
{-1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
{-1.0f, 0.0f, -1.0f, 0.5f, 1.0f},

// bottom right face
{-1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
{1.0f, 0.0f, -1.0f, 1.0f, 0.0f},
{1.0f, 0.0f, 1.0f, 0.5f, 1.0f},
};

// clang-format on

PyramidMesh::PyramidMesh(const std::string &identifier) : Mesh(identifier)
{
    Shader vertex_shader("resources/shaders/debug/debug.vs", GL_VERTEX_SHADER);
    Shader fragment_shader("resources/shaders/debug/debug.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.get_id());
    m_shader_program.add_shader(fragment_shader.get_id());
    m_shader_program.link();

    m_VAO.bind();
    m_VBO.bind();
    m_VAO.set(0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
    m_VAO.set(1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    m_VBO.initialize(m_vertices, sizeof(m_vertices), GL_DYNAMIC_DRAW);
    m_VAO.unbind();
    m_VBO.unbind();
}

void PyramidMesh::update(double dt)
{
    static float angle = 0.0f;
    float rotation_speed = 30.0f; // degrees per second

    angle += rotation_speed * dt;
    if (angle >= 360.0f)
        angle -= 360.0f;

    set_model(glm::translate(glm::mat4(1.0f), position()));
    set_model(glm::rotate(model(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)));
    set_model(glm::translate(model(), -position()));

    Mesh::update(dt);
}

void PyramidMesh::draw(const glm::mat4 &view, const glm::mat4 &model, const glm::mat4 &projection)
{
    m_shader_program.bind();
    m_VBO.bind();
    m_VAO.bind();

    m_shader_program.set_mat4("view", view);
    m_shader_program.set_mat4("model", model * Mesh::model());
    m_shader_program.set_mat4("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 18);

    m_VAO.unbind();
    m_VBO.unbind();

    Mesh::draw(view, model, projection);
}