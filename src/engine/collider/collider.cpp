#include <engine/collider/collider.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

AABB::AABB(const glm::vec3 &min, const glm::vec3 &max) : m_Min(min), m_Max(max), m_Colliding(false)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
}

void AABB::Translate(const glm::vec3 &translation)
{
    m_Min = m_RefMin + translation;
    m_Max = m_RefMax + translation;

    UpdateVertices();
}

void AABB::Update(const std::vector<glm::vec3> &vertices)
{
    m_Min = glm::vec3(FLT_MAX);
    m_Max = glm::vec3(-FLT_MAX);

    for (auto &vertex : vertices)
    {
        m_Min = glm::min(m_Min, vertex);
        m_Max = glm::max(m_Max, vertex);
    }

    m_RefMin = m_Min;
    m_RefMax = m_Max;

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
    return (m_Min.x <= other.m_Max.x && m_Max.x >= other.m_Min.x) && (m_Min.y <= other.m_Max.y && m_Max.y >= other.m_Min.y) &&
           (m_Min.z <= other.m_Max.z && m_Max.z >= other.m_Min.z);
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
        { m_Min.x, m_Min.y, m_Min.z },   
        { m_Max.x, m_Min.y, m_Min.z },    
        { m_Min.x, m_Max.y, m_Min.z },   
        { m_Max.x, m_Max.y, m_Min.z },     
        { m_Min.x, m_Min.y, m_Max.z },   
        { m_Max.x, m_Min.y, m_Max.z },    
        { m_Min.x, m_Max.y, m_Max.z },    
        { m_Max.x, m_Max.y, m_Max.z }    
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