#pragma once

#include <glad/gl.h>

namespace engine
{

class VBO
{
  public:
    VBO();

    void bind();
    static void unbind();

    void initialize(const void *, unsigned int, unsigned int);

    GLuint get_id() const;

    ~VBO();

  private:
    GLuint m_id;
};

}; // namespace engine