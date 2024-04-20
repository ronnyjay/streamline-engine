#pragma once

#include <engine/stb/stb_image.hpp>

#include <glad/gl.h>

#include <string>

namespace engine
{

class texture
{
  public:
    texture(const std::basic_string<char>);

    void bind();
    void unbind()
    {
        glBindTexture(GL_TEXTURE_BINDING_2D, 0);
    }

    GLuint id() const;

    ~texture();

    int m_width;
    int m_height;
    int m_channels;

  private:
    GLuint m_id;
};

}; // namespace engine