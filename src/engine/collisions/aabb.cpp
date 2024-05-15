#include <engine/collisions/aabb.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace engine;

AABB::AABB()
{
    Shader vertex_shader("resources/shaders/box/box.vs", GL_VERTEX_SHADER);
    Shader fragment_shader("resources/shaders/box/box.fs", GL_FRAGMENT_SHADER);

    m_shader_program.add_shader(vertex_shader.get_id());
    m_shader_program.add_shader(fragment_shader.get_id());
    m_shader_program.link();
}

void AABB::initialize(const std::vector<Vertex> &vertices)
{
    Vertex min = vertices[0];
    Vertex max = vertices[0];

    for (const auto &vertex : vertices)
    {
        min.x = std::min(min.x, vertex.x);
        min.y = std::min(min.y, vertex.y);
        min.z = std::min(min.z, vertex.z);

        max.x = std::max(max.x, vertex.x);
        max.y = std::max(max.y, vertex.y);
        max.z = std::max(max.z, vertex.z);
    }

    // clang-format off
    std::vector<Vertex> box_vertices = {
        { min.x, min.y, min.z },    // bottom back-left 
        { max.x, min.y, min.z },    // bottom back-right 
        { min.x, max.y, min.z },    // top back-left 
        { max.x, max.y, min.z },    // top back-right 
        { min.x, min.y, max.z },    // bottom front-left
        { max.x, min.y, max.z },    // bottom front-right 
        { min.x, max.y, max.z },    // top front left 
        { max.x, max.y, max.z }     // top front right 
    };

    std::vector<Index> box_indices = {
        0, 1, 0, 4, 1, 5, 4, 5,     // bottom face
        2, 3, 6, 7, 2, 6, 3, 7,     // top face
        0, 2, 1, 3, 4, 6, 5, 7,     // connecting edges
        2, 7, 3, 6, 4, 1, 5, 0,     // top, bottom diagnals
        4, 7, 6, 5, 2, 1, 0, 3,     // front, back diagnals
        1, 7, 3, 5, 2, 4, 6, 0,     // left, right diagnals
    };
    // clang-format on

    m_vao.bind();
    m_vbo.bind();
    m_ebo.bind();

    m_vao.set(0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);

    m_vbo.initialize(&box_vertices[0], box_vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
    m_ebo.initialize(&box_indices[0], box_indices.size() * sizeof(Index), GL_STATIC_DRAW);

    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();
}

void AABB::update(const std::vector<Point> &points, const glm::mat4 &model)
{
    Vertex min(FLT_MAX);
    Vertex max(-FLT_MAX);

    for (const auto &point : points)
    {
        glm::vec4 vector = model * glm::vec4(point[0], point[1], point[2], 1.0f);

        min.x = std::min(min.x, vector.x);
        min.y = std::min(min.y, vector.y);
        min.z = std::min(min.z, vector.z);

        max.x = std::max(max.x, vector.x);
        max.y = std::max(max.y, vector.y);
        max.z = std::max(max.z, vector.z);
    }

    // clang-format off
    std::vector<Vertex> box_vertices = {
        { min.x, min.y, min.z },    // bottom back-left 
        { max.x, min.y, min.z },    // bottom back-right 
        { min.x, max.y, min.z },    // top back-left 
        { max.x, max.y, min.z },    // top back-right 
        { min.x, min.y, max.z },    // bottom front-left
        { max.x, min.y, max.z },    // bottom front-right 
        { min.x, max.y, max.z },    // top front left 
        { max.x, max.y, max.z }     // top front right 
    };
    // clang-format on

    m_vbo.bind();
    m_vbo.initialize(&box_vertices[0], box_vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
    m_vbo.unbind();
}

void AABB::draw(const glm::mat4 &view, const glm::mat4 &projection)
{
    m_vbo.bind();
    m_vao.bind();
    m_ebo.bind();

    m_shader_program.bind();
    m_shader_program.set_mat4("view", view);
    m_shader_program.set_mat4("model", glm::mat4(1.0f));
    m_shader_program.set_mat4("projection", projection);

    glDrawElements(GL_LINES, 48, GL_UNSIGNED_INT, nullptr);

    m_ebo.unbind();
    m_vao.unbind();
    m_vbo.unbind();
}
