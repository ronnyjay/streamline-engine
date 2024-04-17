#include <engine/mesh/circle/circle.hpp>

using namespace engine;

mesh::circle::circle()
{
    const int vertices = 36;

    float radius = 2.0f;

    for (int i = 0; i <= vertices; i++)
    {
        float theta = 2.0f * M_PI * i / vertices;

        // pos
        m_data.push_back(radius * cosf(theta));
        m_data.push_back(radius * sinf(theta));
        m_data.push_back(10.0f);

        // color
        m_data.push_back(0.3f);
        m_data.push_back(0.3f);
        m_data.push_back(1.0f);

        // normal (pointing out of screen)
        m_data.push_back(0.0f);
        m_data.push_back(0.0f);
        m_data.push_back(-1.0f);
    }

    engine::shader vertex_shader("resources/shaders/default/default.vs", GL_VERTEX_SHADER);
    engine::shader fragment_shader("resources/shaders/default/default.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.id());
    m_shader_program.add_shader(fragment_shader.id());
    m_shader_program.link();

    m_vao.bind();
    m_vbo.bind();
    m_vao.set(0, 3, GL_FLOAT, 9 * sizeof(float), (void *)0);                   // pos
    m_vao.set(1, 3, GL_FLOAT, 9 * sizeof(float), (void *)(3 * sizeof(float))); // color
    m_vao.set(2, 3, GL_FLOAT, 9 * sizeof(float), (void *)(6 * sizeof(float))); // normal
    m_vbo.init(&m_data[0], (m_data.size() * sizeof(float)), GL_DYNAMIC_DRAW);
    m_vao.unbind();
    m_vbo.unbind();
}

void mesh::circle::update(double dt)
{
}

void mesh::circle::draw(glm::mat4 projection, glm::mat4 view)
{
    m_shader_program.bind();

    m_vbo.bind();
    m_vao.bind();

    m_shader_program.set_mat4("model", m_matrix_model);
    m_shader_program.set_mat4("view", view);
    m_shader_program.set_mat4("projection", projection);

    glDrawArrays(GL_TRIANGLE_FAN, 0, m_data.size() / 6);

    m_vao.unbind();
}
