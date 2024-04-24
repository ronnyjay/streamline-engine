#pragma once

#include <glad/gl.h>

namespace engine
{

class EBO
{
  public:
    EBO();

    void bind();
    void unbind();
    void init(const void *data, unsigned int size, unsigned int usage);

    GLuint get_id() const;

    ~EBO();

  private:
    GLuint m_id;
};

}; // namespace engine