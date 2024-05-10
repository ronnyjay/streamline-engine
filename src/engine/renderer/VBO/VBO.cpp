#include <engine/renderer/VBO/VBO.hpp>

using namespace engine;

VBO::VBO()
{
    glGenBuffers(1, &m_id);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::initialize(const void *data, unsigned int size, unsigned int usage)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

GLuint VBO::get_id() const
{
    return m_id;
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_id);
}