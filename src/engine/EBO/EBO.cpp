#include <engine/EBO/EBO.hpp>

using namespace engine;

EBO::EBO()
{
    glGenBuffers(1, &m_id);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::init(const void *data, unsigned int size, unsigned int usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

GLuint EBO::get_id() const
{
    return m_id;
}

EBO::~EBO()
{
    glDeleteBuffers(1, &m_id);
}