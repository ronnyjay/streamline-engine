#include <engine/collider/collider.hpp>

#include <glm/common.hpp>
#include <glm/ext/scalar_common.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

AABB::AABB(std::shared_ptr<Model> model)
    : m_Min(FLT_MAX)
    , m_Max(-FLT_MAX)
    , m_Colliding(false)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    for (const auto &mesh : model->GetMeshes())
    {
        for (const auto &vertex : mesh.GetVertices())
        {
            m_Min = glm::min(m_Min, vertex.Position);
            m_Max = glm::max(m_Max, vertex.Position);
        }
    }

    m_RefMin = m_Min;
    m_RefMax = m_Max;

    UpdateVertices();
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
    return (m_Min.x <= other.m_Max.x && m_Max.x >= other.m_Min.x) &&
           (m_Min.y <= other.m_Max.y && m_Max.y >= other.m_Min.y) &&
           (m_Min.z <= other.m_Max.z && m_Max.z >= other.m_Min.z);
}

// Collision AABB::Intersects(const AABB &other)
// {
//     Collision collision;

//     glm::vec3 halfExtentsA = (m_Max - m_Min) * 0.5f;
//     glm::vec3 halfExtentsB = (other.m_Max - other.m_Min) * 0.5f;
//     glm::vec3 centerA = (m_Max + m_Min) * 0.5f;
//     glm::vec3 centerB = (other.m_Max + other.m_Min) * 0.5f;
//     glm::vec3 delta = (centerB - centerA);
//     glm::vec3 overlap = halfExtentsA + halfExtentsB - glm::abs(delta);

//     if (overlap.x > 0 && overlap.y > 0 && overlap.z > 0)
//     {
//         collision.Depth = overlap;

//         if (overlap.x < overlap.y && overlap.x < overlap.z)
//         {
//             collision.Normal = glm::vec3((delta.x > 0) ? -1.0f : 1.0f, 0.0f, 0.0f);
//         }
//         else if (overlap.y < overlap.x && overlap.y < overlap.z)
//         {
//             collision.Normal = glm::vec3(0.0f, (delta.y > 0) ? -1.0f : 1.0f, 0.0f);
//         }
//         else
//         {
//             collision.Normal = glm::vec3(0.0f, 0.0f, (delta.z > 0) ? -1.0f : 1.0f);
//         }

//         collision.Collided = true;
//     }

//     return collision;
// }

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