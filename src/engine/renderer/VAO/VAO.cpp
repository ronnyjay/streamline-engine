#include <engine/renderer/VAO/VAO.hpp>

using namespace engine;

VAO::VAO()
{
    glGenVertexArrays(1, &m_id);
}

void VAO::bind()
{
    glBindVertexArray(m_id);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::set(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}

void VAO::set_int(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer)
{
    glEnableVertexAttribArray(index);
    glVertexAttribIPointer(index, size, type, stride, pointer);
}

GLuint VAO::get_id() const
{
    return m_id;
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_id);
}