#pragma once

#include <glad/gl.h>

namespace engine
{

class VAO
{
  public:
    VAO();

    void bind();
    static void unbind();

    void set(unsigned int, unsigned int, unsigned int, unsigned int, const void *);
    void set_int(unsigned int, unsigned int, unsigned int, unsigned int, const void *);

    GLuint get_id() const;

    ~VAO();

  private:
    GLuint m_id;
};

}; // namespace engine