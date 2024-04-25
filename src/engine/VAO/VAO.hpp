#pragma once

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace engine
{

class VAO
{
  public:
    VAO();

    void bind();
    static void unbind();

    void set(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer);
    void set_int(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, const void *pointer);

    GLuint get_id() const;

    ~VAO();

  private:
    GLuint m_id;
};

}; // namespace engine