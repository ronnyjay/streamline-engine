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

    GLuint id() const;

    ~texture();

  private:
    int m_width;
    int m_height;
    int m_channels;

    GLuint m_id;
};

}; // namespace engine