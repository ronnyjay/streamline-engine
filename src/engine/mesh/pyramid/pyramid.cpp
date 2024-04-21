#include <engine/mesh/pyramid/pyramid.hpp>
#include <glm/fwd.hpp>

using namespace engine::mesh;

// clang-format off
const GLfloat pyramid::m_data[][5] = {

// front face               
{-1.0f, 0.0f, 9.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 9.0f, 1.0f, 0.f},
{0.0f, 2.0f, 10.0f, 0.5f, 1.0f},

// back face
{-1.0f, 0.0f, 11.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 11.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 10.0f, 0.5f, 1.0f},

// left face
{-1.0f, 0.0f, 9.0f, 0.0f, 0.0f},
{-1.0f, 0.0f, 11.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 10.0f, 0.5f, 1.0f},

// right face
{1.0f, 0.0f, 11.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 9.0f, 1.0f, 0.0f},
{0.0f, 2.0f, 10.0f, 0.5f, 1.0f},

// bottom left face           
{1.0f, 0.0f, 9.0f, 0.0f, 0.0f},
{-1.0f, 0.0f, 9.0f, 1.0f, 0.0f},
{-1.0f, 0.0f, 11.0f, 0.5f, 1.0f},

// bottom right face
{-1.0f, 0.0f, 11.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 11.0f, 1.0f, 0.0f},
{1.0f, 0.0f, 9.0f, 0.5f, 1.0f},

};
// clang-format on

pyramid::pyramid(const std::basic_string<char> &name) : mesh_t(name)
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

void pyramid::update(double dt)
{
    static float angle = 0.0f;
    float rotation_speed = 30.0f; // degrees per second

    angle += rotation_speed * dt;
    if (angle >= 360.0f)
        angle -= 360.0f;

    m_model = glm::translate(glm::mat4(1.0f), m_pos);
    m_model = glm::translate(m_model, glm::vec3(0.0f, 1.0f, 10.0f));
    m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::translate(m_model, glm::vec3(0.0f, -1.0f, -10.0f));

    mesh_t::update(dt);
}

void pyramid::draw(const glm::mat4 &model, const glm::mat4 &projection, const glm::mat4 &view)
{
    m_shader_program.bind();
    m_vbo.bind();
    m_vao.bind();

    m_shader_program.set_mat4("model", model + m_model);
    m_shader_program.set_mat4("view", view);
    m_shader_program.set_mat4("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 18);

    m_vao.unbind();
    m_vbo.unbind();

    mesh_t::draw(model, projection, view);
}
