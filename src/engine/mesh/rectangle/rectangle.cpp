#include "engine/mesh/mesh.hpp"
#include <engine/mesh/rectangle/rectangle.hpp>
#include <glm/fwd.hpp>

using namespace engine::mesh;

// clang-format off
const GLfloat rectangle::m_data[4][5] = {
    {-1.0f, -1.0f, 10.0f, 0.0f, 0.0f},  
    {+1.0f, -1.0f, 10.0f, 1.0f, 0.0f}, 
    {-1.0f, +1.0f, 10.0f, 0.0f, 1.0f},  
    {+1.0f, +1.0f, 10.0f, 1.0f, 1.0f}   
};
// clang-format on

rectangle::rectangle(const std::basic_string<char> &name) : mesh_t(name)
{

    shader vertex_shader("resources/shaders/debug/debug.vs", GL_VERTEX_SHADER);
    shader fragment_shader("resources/shaders/debug/debug.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.id());
    m_shader_program.add_shader(fragment_shader.id());
    m_shader_program.link();

    m_vao.bind();
    m_vbo.bind();
    m_vao.set(0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
    m_vao.set(1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    m_vbo.init(m_data, sizeof(m_data), GL_DYNAMIC_DRAW);
    m_vao.unbind();
    m_vbo.unbind();
}

void rectangle::update(double dt)
{
    m_model = glm::translate(glm::mat4(1.0f), m_pos);
}

void rectangle::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    m_shader_program.bind();
    m_vbo.bind();
    m_vao.bind();

    m_shader_program.set_mat4("model", model + m_model);
    m_shader_program.set_mat4("view", view);
    m_shader_program.set_mat4("projection", projection);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_vao.unbind();
    m_vbo.unbind();

    mesh_t::draw(model, view, projection);
}
