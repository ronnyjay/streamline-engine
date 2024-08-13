#include <engine/Components/BSphere.hpp>

#include <glm/gtx/norm.hpp>

using namespace engine;

BSphere::BSphere(std::shared_ptr<Model> model)
    : m_Radius(0.0f)
    , m_Center(0.0f)
    , m_Translation(0.0f)
{
    int vertexCount = 0;

    for (const auto &mesh : model.get()->GetMeshes())
    {
        auto &vertices = mesh.GetVertices();

        for (const auto &vertex : vertices)
        {
            m_Center += vertex.Position;
        }

        vertexCount += vertices.size();
    }

    if (vertexCount)
    {
        m_Center /= vertexCount;

        float maxDistance = 0.0f;

        for (const auto &mesh : model.get()->GetMeshes())
        {
            for (const auto &vertex : mesh.GetVertices())
            {
                float distance = glm::distance2(m_Center, vertex.Position);

                if (distance > maxDistance)
                {
                    maxDistance = distance;
                }
            }
        }

        m_Radius = sqrt(maxDistance);
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    UpdateVertices();
}

BSphere::BSphere(BSphere &&other)
    : m_Radius(other.m_Radius)
    , m_Center(other.m_Center)
    , m_Translation(other.m_Translation)
    , m_VAO(other.m_VAO)
    , m_VBO(other.m_VBO)
    , m_EBO(other.m_EBO)
{
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;
}

float BSphere::Radius() const
{
    return m_Radius;
}

const glm::vec3 &BSphere::Center() const
{
    return m_Center;
}

const glm::vec3 &BSphere::Translation() const
{
    return m_Translation;
}

void BSphere::Update(const std::vector<glm::vec3> &vertices)
{
    int vertexCount = 0;

    for (const auto &vertex : vertices)
    {
        m_Center += vertex;
    }

    vertexCount += vertices.size();

    if (vertexCount)
    {
        m_Center /= vertexCount;

        float maxDistance = 0.0f;

        for (const auto &vertex : vertices)
        {
            float distance = glm::distance2(m_Center, vertex);

            if (distance > maxDistance)
            {
                maxDistance = distance;
            }
        }

        m_Radius = sqrt(maxDistance);
    }

    UpdateVertices();
}

void BSphere::Translate(const glm::vec3 &translation)
{
    m_Center -= m_Translation;

    m_Translation = translation;

    m_Center += m_Translation;
}

void BSphere::Draw()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, (32 - 1) * (64 - 1) * 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void BSphere::UpdateVertices()
{
    const float R = 1.0f / (RINGS - 1);
    const float S = 1.0f / (SEGMENTS - 1);

    std::vector<glm::vec3> vertices;

    for (unsigned int r = 0; r < RINGS; r++)
    {
        for (unsigned int s = 0; s < SEGMENTS; s++)
        {
            float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float y = cos(M_PI * r * R);
            float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            vertices.push_back(glm::vec3(x, y, z) * m_Radius + m_Translation);
        }
    }

    std::vector<GLuint> indices;

    for (unsigned int r = 0; r < RINGS - 1; r++)
    {
        for (unsigned int s = 0; s < SEGMENTS - 1; s++)
        {
            indices.push_back(r * SEGMENTS + (s + 1));
            indices.push_back((r + 1) * SEGMENTS + (s + 1));

            indices.push_back((r + 1) * SEGMENTS + (s + 1));
            indices.push_back((r + 1) * SEGMENTS + s);
        }
    }

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    glBindVertexArray(0);
}

BSphere::~BSphere()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}