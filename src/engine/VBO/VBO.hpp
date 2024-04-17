#pragma once

#include <glad/gl.h>

namespace engine
{

class VBO
{
  public:
    VBO();

    void bind();
    void unbind();
    void init(const void *data, unsigned int size, unsigned int usage);

    GLuint get_id() const;

    ~VBO();

  private:
    GLuint m_id;
};

}; // namespace engine