#pragma once

#include <glad/gl.h>

namespace engine
{

class EBO
{
  public:
    EBO();

    void bind();
    static void unbind();

    void initialize(unsigned int, const void *, unsigned int);

    GLuint get_id() const;

    ~EBO();

  private:
    GLuint m_id;
};

}; // namespace engine