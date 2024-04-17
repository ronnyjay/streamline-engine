#pragma once

#include <glad/gl.h>

namespace engine
{

class EBO
{
    EBO();

    void bind();
    void init(const void *data, unsigned int size, unsigned int usage);

    GLuint get_id() const;

    ~EBO();

  private:
    GLuint m_id;
};

}; // namespace engine