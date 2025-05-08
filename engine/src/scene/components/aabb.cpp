#include "scene/components/aabb.hpp"

#include "math/component_wise.hpp"
#include "math/quaternion.hpp"
#include "math/transformation.hpp"

#include <limits>
#include <memory>

using namespace engine;

AABB::AABB(const std::shared_ptr<Model> &model)
    : m_globalMin(std::numeric_limits<float>::max())
    , m_globalMax(std::numeric_limits<float>::min())
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    for (const auto &mesh : model->meshes)
    {
        for (const auto &vertex : mesh.getVertices())
        {
            m_globalMin = engine::min(m_globalMin, vertex.position);
            m_globalMax = engine::max(m_globalMax, vertex.position);

            m_vertexData.emplace_back(vertex.position);
        }
    }

    m_localMin    = m_globalMin;
    m_localMax    = m_globalMax;
    m_center      = (m_globalMax + m_globalMin) * 0.5f;
    m_halfExtents = (m_globalMax - m_globalMin) * 0.5f;

    updateVertices();
}

AABB::AABB(AABB &&other)
    : m_globalMin(other.m_globalMin)
    , m_globalMax(other.m_globalMax)
    , m_localMin(other.m_localMin)
    , m_localMax(other.m_localMax)
    , m_VAO(other.m_VAO)
    , m_VBO(other.m_VBO)
    , m_EBO(other.m_EBO)
{
    other.m_VAO    = 0;
    other.m_VBO    = 0;
    other.m_EBO    = 0;

    m_center       = other.m_center;
    m_halfExtents  = other.m_halfExtents;

    m_lastScale    = other.m_lastScale;
    m_lastRotation = other.m_lastRotation;
}

AABB::~AABB()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void AABB::translate(const vec3 &translation)
{
    m_globalMin   = m_localMin + translation;
    m_globalMax   = m_localMax + translation;

    m_center      = (m_globalMax + m_globalMin) * 0.5f;
    m_halfExtents = (m_globalMax - m_globalMin) * 0.5f;

    updateVertices();
}

void AABB::rotate(const vec3 &rotation)
{
    if (rotation == m_lastRotation)
    {
        return;
    }

    mat4 rotationMatrix = toMat4(quat(rotation));

    m_globalMin         = std::numeric_limits<float>::max();
    m_globalMax         = std::numeric_limits<float>::min();

    for (const auto &vertex : m_vertexData)
    {
        vec3 rotatedVertex = vec3(rotationMatrix * vec4(vertex, 1.0f));

        m_globalMin        = engine::min(m_globalMin, rotatedVertex);
        m_globalMax        = engine::max(m_globalMax, rotatedVertex);
    }

    m_localMin     = m_globalMin;
    m_localMax     = m_globalMax;

    m_center       = (m_globalMax + m_globalMin) * 0.5f;
    m_halfExtents  = (m_globalMax - m_globalMin) * 0.5f;

    m_lastRotation = rotation;

    updateVertices();
}

void AABB::scale(const vec3 &scale)
{
    if (scale == m_lastScale)
    {
        return;
    }

    mat4 scalingMatrix = ::scale(mat4(1.0f), scale);

    m_globalMin        = std::numeric_limits<float>::max();
    m_globalMax        = std::numeric_limits<float>::min();

    for (const auto &vertex : m_vertexData)
    {
        vec3 scaledVertex = vec3(scalingMatrix * vec4(vertex, 1.0f));

        m_globalMin       = engine::min(m_globalMin, scaledVertex);
        m_globalMax       = engine::max(m_globalMax, scaledVertex);
    }

    m_localMin    = m_globalMin;
    m_localMax    = m_globalMax;

    m_center      = (m_globalMax + m_globalMin) * 0.5f;
    m_halfExtents = (m_globalMax - m_globalMin) * 0.5f;

    m_lastScale   = scale;

    updateVertices();
}

const vec3 &AABB::min() const
{
    return m_globalMin;
}

const vec3 &AABB::max() const
{
    return m_globalMax;
}

const vec3 &AABB::center() const
{
    return m_center;
}

const vec3 &AABB::halfExtents() const
{
    return m_halfExtents;
}

void AABB::draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, 48, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void AABB::updateVertices()
{
    // clang-format off
    const std::vector<vec3> vertices = {
        { m_globalMin.x, m_globalMin.y, m_globalMin.z },   
        { m_globalMax.x, m_globalMin.y, m_globalMin.z },    
        { m_globalMin.x, m_globalMax.y, m_globalMin.z },   
        { m_globalMax.x, m_globalMax.y, m_globalMin.z },     
        { m_globalMin.x, m_globalMin.y, m_globalMax.z },   
        { m_globalMax.x, m_globalMin.y, m_globalMax.z },    
        { m_globalMin.x, m_globalMax.y, m_globalMax.z },    
        { m_globalMax.x, m_globalMax.y, m_globalMax.z }    
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);

    glBindVertexArray(0);
}
