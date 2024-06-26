#include <engine/Components/AABB.hpp>

using namespace engine;

AABB::AABB(std::shared_ptr<Model> model)
    : m_GlobalMin(FLT_MAX)
    , m_GlobalMax(-FLT_MAX)
    , m_Colliding(false)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    for (const auto &mesh : model.get()->GetMeshes())
    {
        for (const auto &vertex : mesh.GetVertices())
        {
            m_GlobalMin = glm::min(m_GlobalMin, vertex.Position);
            m_GlobalMax = glm::max(m_GlobalMax, vertex.Position);
        }
    }

    m_LocalMin = m_GlobalMin;
    m_LocalMax = m_GlobalMax;

    UpdateVertices();
}

void AABB::Translate(const glm::vec3 &translation)
{
    m_GlobalMin = m_LocalMin + translation;
    m_GlobalMax = m_LocalMax + translation;

    UpdateVertices();
}

void AABB::Update(const std::vector<glm::vec3> &vertices)
{
    m_GlobalMin = glm::vec3(FLT_MAX);
    m_GlobalMax = glm::vec3(-FLT_MAX);

    for (auto &vertex : vertices)
    {
        m_GlobalMin = glm::min(m_GlobalMin, vertex);
        m_GlobalMax = glm::max(m_GlobalMax, vertex);
    }

    m_LocalMin = m_GlobalMin;
    m_LocalMax = m_GlobalMax;

    UpdateVertices();
}

void AABB::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, 48, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

bool AABB::Intersects(const AABB &other)
{
    return (m_GlobalMin.x <= other.m_GlobalMax.x && m_GlobalMax.x >= other.m_GlobalMin.x) &&
           (m_GlobalMin.y <= other.m_GlobalMax.y && m_GlobalMax.y >= other.m_GlobalMin.y) &&
           (m_GlobalMin.z <= other.m_GlobalMax.z && m_GlobalMax.z >= other.m_GlobalMin.z);
}

bool AABB::GetColliding() const
{
    return m_Colliding;
}

void AABB::SetColliding(const bool colliding)
{
    m_Colliding = colliding;
}

void AABB::UpdateVertices()
{
    // clang-format off
    const std::vector<glm::vec3> vertices = {
        { m_GlobalMin.x, m_GlobalMin.y, m_GlobalMin.z },   
        { m_GlobalMax.x, m_GlobalMin.y, m_GlobalMin.z },    
        { m_GlobalMin.x, m_GlobalMax.y, m_GlobalMin.z },   
        { m_GlobalMax.x, m_GlobalMax.y, m_GlobalMin.z },     
        { m_GlobalMin.x, m_GlobalMin.y, m_GlobalMax.z },   
        { m_GlobalMax.x, m_GlobalMin.y, m_GlobalMax.z },    
        { m_GlobalMin.x, m_GlobalMax.y, m_GlobalMax.z },    
        { m_GlobalMax.x, m_GlobalMax.y, m_GlobalMax.z }    
    };

    const std::vector<GLuint> indices = {
        0, 1, 0, 4, 1, 5, 4, 5,     
        2, 3, 6, 7, 2, 6, 3, 7,     
        0, 2, 1, 3, 4, 6, 5, 7,    
        2, 7, 3, 6, 4, 1, 5, 0,    
        4, 7, 6, 5, 2, 1, 0, 3,     
        1, 7, 3, 5, 2, 4, 6, 0,     
    };
    // clang-format on

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    glBindVertexArray(0);
}

AABB::~AABB()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
